package main

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
	"strings"
	"sync"

	"github.com/aDotInTheVoid/wacc.wacc/test/runner"
)

var bs2 string
var wacc string

var update = os.Getenv("WACC_UPDATE") == "1"
var refComp = bs2

type runResult int

const (
	runResultPass = iota
	runResultFail
)

type runData struct {
	Path     string
	Compiler string
	Result   runResult
	Stdin    string
	Stderr   string
	Stdout   string
	ExitCode int
}

var compilers = []runner.Compiler{runner.BS2{}, runner.WaccWacc{}, runner.WaccToC{}}

func main() {
	log.SetFlags(0)
	gotoTestDir()

	for _, c := range compilers {
		runner.Must(c.Ensure())
	}

	var wg sync.WaitGroup
	c := make(chan runData)
	done := make(chan struct{})

	filepath.Walk("lex-pass", walkWrap(bs2LexPass, c, &wg))
	filepath.Walk("lex-pass", walkWrap(waccLexPass, c, &wg))

	// Wait for all the tests to finish
	// Must go this after all runs
	go func() {
		wg.Wait()
		done <- struct{}{}
	}()

	nPass := 0
	nFail := 0
	status := ""

loop:
	for {
		select {
		case r := <-c:
			if r.Result == runResultFail {
				nFail++
				status = "FAIL"
			} else {
				nPass++
				status = "PASS"
			}
			fmt.Printf("%s: %5s %s\n", status, filepath.Base(r.Compiler), r.Path)
		case <-done:
			break loop
		}
	}

	log.Printf("%d passed, %d failed", nPass, nFail)
	if nFail != 0 {
		println("======== FAILED =========")
		os.Exit(1)
	}
}

type TestOverallRunner func(path string) runData

func bs2LexPass(path string) runData {
	output := runner.RunOutputGet(bs2, path)
	var status runResult
	if output.Status != 0 {
		status = runResultFail
	} else {
		status = runResultPass
	}
	// TODO: Encode that bs2 is the reference compiler
	if update {
		os.WriteFile(stdoutFile(path), []byte(output.Stdout), 0644)
	} else {
		c, err := os.ReadFile(stdoutFile(path))
		runner.Must(err)
		if string(c) != output.Stdout {
			status = runResultFail
			// TODO: Better message
		}
	}

	return runData{
		Path:     path,
		Compiler: bs2,
		Result:   status,
		Stdin:    path,
		Stderr:   output.Stderr,
		Stdout:   output.Stdout,
		ExitCode: output.Status,
	}
}
func waccLexPass(path string) runData {

	output := runner.RunOutputGet(wacc, path)
	var status runResult
	if output.Status != 0 {
		status = runResultFail
	} else {
		status = runResultPass
	}
	if !update {

		c, err := os.ReadFile(stdoutFile(path))
		runner.Must(err)
		if string(c) != output.Stdout {
			status = runResultFail
			// TODO: Better message
			panic("Path(wacc) = " + path + "\nExpectesd ```" + string(c) + "``` got ```" + output.Stdout + "```")
		}
	}
	return runData{
		Path:     path,
		Compiler: wacc,
		Result:   status,
		Stdin:    path,
		Stderr:   output.Stderr,
		Stdout:   output.Stdout,
		ExitCode: output.Status,
	}
}

func walkWrap(f TestOverallRunner, c chan runData, wg *sync.WaitGroup) filepath.WalkFunc {
	return func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		if info.IsDir() {
			return nil
		}
		if filepath.Ext(path) != ".wacc" {
			return nil
		}
		wg.Add(1)
		go func() {
			c <- f(path)
			wg.Done()
		}()

		return nil
	}
}

func gotoTestDir() {
	if td := os.Getenv("WACC_TEST_DIR"); td != "" {
		runner.Must(os.Chdir(td))
	} else {
		for {
			if runner.DirExists("test") {
				runner.Must(os.Chdir("test"))
				return
			}
			cwd, err := os.Getwd()
			runner.Must(err)
			if cwd == "/" {
				break
			}
			runner.Must(os.Chdir(".."))
		}
	}
	if !runner.DirExists("runner") {
		log.Fatal("Failed to find test directory")
	}
}

func findCompillers() {
	// bs2
	if !runner.DirExists("../bs2") {
		log.Fatal("Failed to find bs2 directory")
	}
	if !runner.DirExists("../bs2/_build/test") {
		runner.RunBuildCmd("../bs2", "meson", "_build/test")
	}
	runner.RunBuildCmd("../bs2", "ninja", "-C", "_build/test")
	bs2 = "../bs2/_build/test/bs2"

	// wacc
	runner.RunBuildCmd("..", "make", "_build/wacc")
	wacc = "../_build/wacc"
}

func (r *runData) visual() string {
	var b strings.Builder
	b.WriteString("Command ")
	b.WriteString(r.Compiler)
	b.WriteString(" < ")
	b.WriteString(r.Path)
	b.WriteString(" exited with code ")
	b.WriteString(fmt.Sprintf("%d", r.ExitCode))
	if r.Stdout != "" {
		b.WriteString("\n--- stdout ---------------------------------------\n")
		b.WriteString(strings.TrimSpace(r.Stdout))
		b.WriteString("\n----------------------------------------------------\n")
	} else {
		b.WriteString("\nstdout: none\n")
	}
	if r.Stderr != "" {
		b.WriteString("\n--- stderr ---------------------------------------\n")
		b.WriteString(strings.TrimSpace(r.Stderr))
		b.WriteString("\n----------------------------------------------------\n")
	} else {
		b.WriteString("\nstderr: none\n")
	}
	return b.String()
}

func stdoutFile(path string) string {
	ext := filepath.Ext(path)
	return path[:len(path)-len(ext)] + ".stdout"
}

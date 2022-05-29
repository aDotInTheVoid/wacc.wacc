package main

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
	"sync"

	"github.com/aDotInTheVoid/wacc.wacc/test/runner"
	"github.com/adotinthevoid/xmlpp"
	"github.com/fatih/color"
)

var isBlessEnabled = os.Getenv("WACC_UPDATE") == "1"

type runResult int

const (
	runResultPass = iota
	runResultFail

	// Normal test
	blessDisabled = iota
	blessEnabledAuthoritative
	blessEnabledNonAuthoritative
)

type blessMode = int

type runData struct {
	Path     string
	Compiler string
	Result   runResult
	Message  string
}

var compilers = []runner.Compiler{runner.BS2, runner.WaccWacc{}, runner.WaccToC{}}

func main() {
	log.SetFlags(0)
	gotoTestDir()

	for _, c := range compilers {
		runner.Must(c.Ensure())
	}

	var wg sync.WaitGroup
	c := make(chan runData)
	done := make(chan struct{})

	bs2LexPass := LexPassConfig{runner.BS2, blessDisabled}
	waccWaccLexPass := LexPassConfig{runner.WaccWacc{}, blessDisabled}

	if isBlessEnabled {
		bs2LexPass.blessMode = blessEnabledAuthoritative
		waccWaccLexPass.blessMode = blessEnabledNonAuthoritative
	}
	bs2ParsePass := bs2LexPass

	filepath.Walk("lex-pass", walkWrap(lexPass, c, &wg, bs2LexPass))
	filepath.Walk("lex-pass", walkWrap(lexPass, c, &wg, waccWaccLexPass))
	filepath.Walk("parse-pass", walkWrap(parsePass, c, &wg, bs2ParsePass))

	// Wait for all the tests to finish
	// Must go this after all runs
	go func() {
		wg.Wait()
		done <- struct{}{}
	}()

	nPass := 0
	nFail := 0
	status := ""
	statusFail := color.New(color.FgRed).Add(color.Bold).SprintFunc()("FAIL")
	statusPass := color.GreenString("PASS")

done:
	for {
		select {
		case r := <-c:
			if r.Result == runResultFail {
				nFail++
				status = statusFail
			} else {
				nPass++
				status = statusPass
			}
			fmt.Printf("%s: %10s %s\n", status, filepath.Base(r.Compiler), r.Path)
			if r.Result == runResultFail {
				fmt.Println(r.Message)
			}
		case <-done:
			break done
		}
	}

	log.Printf("%d passed, %d failed", nPass, nFail)
	if nFail != 0 {
		println("======== FAILED =========")
		os.Exit(1)
	}
}

// Result is optional
type TestOverallRunner[T any] func(path string, config T) *runData

type LexPassConfig struct {
	compiler  runner.Compiler
	blessMode blessMode
}

func parsePass(path string, config LexPassConfig) *runData {
	if config.blessMode == blessEnabledNonAuthoritative {
		return nil
	}
	out := config.compiler.Parse(path)
	var status runResult
	if out.StatusCode != 0 {
		status = runResultFail
	} else {
		status = runResultPass
	}

	message := ""

	outXmlT, err := xmlpp.BuildTree(out.Stdout)
	if err != nil {
		status = runResultFail
		message = "Expected XML, got ```" + out.Stdout + "```"
	} else {
		outXml := xmlpp.Pp(&outXmlT)
		if config.blessMode == blessEnabledAuthoritative {
			os.WriteFile(withSuffix(path, "xml"), []byte(outXml), 0644)
		} else {
			c, err := os.ReadFile(withSuffix(path, "xml"))
			runner.Must(err)
			if string(c) != outXml {
				status = runResultFail
			}
			// TODO: Diff
			message = "Expected ---\n" + string(c) + "\n--- got ---\n" + outXml + "\n---"
		}
	}

	return &runData{
		path,
		config.compiler.Name(),
		status,
		message,
	}
}

func lexPass(path string, config LexPassConfig) *runData {
	if config.blessMode == blessEnabledNonAuthoritative {
		return nil
	}

	out := config.compiler.Lex(path)
	var status runResult
	if out.StatusCode != 0 {
		status = runResultFail
	} else {
		status = runResultPass
	}

	message := ""

	if config.blessMode == blessEnabledAuthoritative {
		os.WriteFile(withSuffix(path, "stdout"), []byte(out.Stdout), 0644)
	} else {
		c, err := os.ReadFile(withSuffix(path, "stdout"))
		runner.Must(err)
		if string(c) != out.Stdout {
			status = runResultFail
		}
		message = "Expected ```" + string(c) + "``` got ```" + out.Stdout + "```"
	}

	return &runData{
		path,
		config.compiler.Name(),
		status,
		message,
	}
}

func walkWrap[T any](f TestOverallRunner[T], c chan runData, wg *sync.WaitGroup, config T) filepath.WalkFunc {
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
			result := f(path, config)
			if result != nil {
				c <- *result
			}
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

func withSuffix(path string, newExt string) string {
	ext := filepath.Ext(path)
	return path[:len(path)-len(ext)] + "." + newExt
}

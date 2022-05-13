package main

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
	"sync"

	"github.com/aDotInTheVoid/wacc.wacc/test/runner"
)

var bs2 string

type runResult int

const (
	runResultPass = iota
	runResultFail
)

type runData struct {
	Path     string
	Compiler string
	Result   runResult
}

func main() {
	log.SetFlags(0)
	gotoTestDir()
	findCompillers()

	var wg sync.WaitGroup
	c := make(chan runData)
	done := make(chan struct{})

	filepath.Walk("lex-pass", walkWrap(bs2LexPass, c, &wg))

	// Wait for all the tests to finish
	// Must go this after all runs
	go func() {
		wg.Wait()
		done <- struct{}{}
	}()

	nPass := 0
	nFail := 0

loop:
	for {
		select {
		case r := <-c:
			if r.Result == runResultFail {
				nFail++
				fmt.Print("FAIL ")
			} else {
				nPass++
				fmt.Print("PASS ")
			}
			fmt.Println(filepath.Base(r.Compiler), " ", r.Path)
		case <-done:
			break loop
		}
	}

	log.Printf("%d passed, %d failed", nPass, nFail)
}

type TestOverallRunner func(path string) runData

func bs2LexPass(path string) runData {
	output := runner.RunOutputGet(bs2, path)
	if output.Status != 0 {
		return runData{path, bs2, runResultFail}
	} else {
		return runData{path, bs2, runResultPass}
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

func dirExists(name string) bool {
	s, err := os.Stat(name)
	if err != nil {
		return false
	}
	return s.IsDir()
}

func gotoTestDir() {
	if td := os.Getenv("WACC_TEST_DIR"); td != "" {
		runner.Must(os.Chdir(td))
	} else {
		for {
			if dirExists("test") {
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
	if !dirExists("runner") {
		log.Fatal("Failed to find test directory")
	}
}

func findCompillers() {
	if !dirExists("../bs2") {
		log.Fatal("Failed to find bs2 directory")
	}
	if !dirExists("../bs2/_build/test") {
		runner.RunBuild("../bs2", "meson", "_build/test")
	}
	runner.RunBuild("../bs2", "ninja", "-C", "_build/test")
	bs2 = "../bs2/_build/test/bs2"
}

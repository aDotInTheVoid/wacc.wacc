package main

import (
	"fmt"
	"log"
	"os"
	"sync"
	"time"

	"github.com/aDotInTheVoid/wacc.wacc/test/runner"
	"github.com/adotinthevoid/xmlpp"
	"github.com/fatih/color"
)

func main() {
	start := time.Now()
	// cwd to root
	for {
		if runner.DirExists("test") &&
			runner.DirExists("bs2") &&
			runner.DirExists("gen") &&
			runner.DirExists("gram") {
			break
		}
		cwd, err := os.Getwd()
		if err != nil {
			log.Fatal("Cannot get cwd", err)
		} else if cwd == "/" {
			log.Fatal("Cannot find root directory")
		}
		err = os.Chdir("..")
		if err != nil {
			log.Fatal("Cannot change directory", err)
		}
	}

	here, err := os.Getwd()
	if err != nil {
		log.Fatal("Cannot get cwd", err)
	}
	log.Println("In dir", here)

	var wg sync.WaitGroup
	c := make(chan runner.TestResult)
	done := make(chan struct{})
	bless := os.Getenv("WACC_UPDATE") == "1"

	lexers := runner.CompilerGroup[runner.Lexer]{
		Authoritative:    runner.BS2Lexer,
		NonAuthoritative: []runner.Lexer{runner.WaccBs2Lexer, runner.WaccTpLexer},
	}
	parsers := runner.CompilerGroup[runner.Parser]{Authoritative: runner.BS2Parser}
	assembles := runner.CompilerGroup[runner.Assembler]{Authoritative: runner.BS2Assembler}
	e := lexers.Ensure()
	if e.IsError() {
		log.Fatalf("Command `%s` exited with %d\n", e.Invocation, e.ExitCode)
	}
	// The bs2 parser and assembler were ensured by the lexer.

	runner.RunSuite("test/lex-pass", "stdout", &lexers, runLex, bless, c, &wg)
	runner.RunSuite("test/parse-pass", "xml", &parsers, runParse, bless, c, &wg)
	runner.RunSuite("test/asm-pass", "s", &assembles, runAsm, bless, c, &wg)

	// All tests are now launched
	go func() {
		wg.Wait()
		done <- struct{}{}
	}()

	nFail := 0
	nPass := 0
results:
	for {
		select {
		case result := <-c:
			if result.IsError() {
				nFail++
				fmt.Fprintf(os.Stderr, "%s %10s %s\n%s\n", color.RedString("FAIL"), result.Compiler, result.TestName, result.Message)
			} else {
				fmt.Fprintf(os.Stderr, "PASS %10s %s\n", result.Compiler, result.TestName)
				nPass++
			}
		case <-done:
			break results
		}
	}

	elapsed := time.Since(start)
	if nFail == 0 {
		fmt.Fprintf(os.Stderr, "Passed %d tests in %s\n", nPass, elapsed)
	} else {
		// fmt.Fprintf(os.Stderr, "!!! Failed %d tests (passed %d) in %s\n", nFail, nPass, elapsed)
		fmt.Fprintln(os.Stderr, color.RedString("!!! Failed %d tests (passed %d) in %s", nFail, nPass, elapsed))
		os.Exit(1)
	}
}

func runLex(l runner.Lexer, path string) runner.CommandResult {
	return l.Lex(path)
}
func runAsm(a runner.Assembler, path string) runner.CommandResult {
	return a.Assemble(path)
}

func runParse(p runner.Parser, path string) runner.CommandResult {
	r := p.Parse(path)
	if r.IsError() {
		return r
	}
	tree, err := xmlpp.BuildTree(r.Output)
	if err != nil {
		r.ExitCode = 1
		r.Error = err.Error()
		return r
	}
	r.Output = xmlpp.Pp(&tree)
	return r
}

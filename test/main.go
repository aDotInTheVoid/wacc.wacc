package main

import (
	"flag"
	"fmt"
	"log"
	"net/http"
	_ "net/http/pprof"
	"os"
	"regexp"
	"sync"
	"time"

	"github.com/aDotInTheVoid/wacc.wacc/test/runner"
	"github.com/adotinthevoid/xmlpp"
	"github.com/fatih/color"
)

var verbose = flag.Bool("v", false, "Verbose")

func main() {
	start := time.Now()
	flag.Parse()

	go func() {
		log.Println(http.ListenAndServe("localhost:6060", nil))
	}()

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
	running := make(map[string]struct{})

	lexers := runner.NewGroup(runner.BS2Lexer, runner.WaccBs2Lexer, runner.WaccTpLexer)
	parsers := runner.NewGroup(runner.BS2Parser)
	assembles := runner.NewGroup(runner.BS2Assembler)
	runners := runner.NewGroup(runner.TPRunner, runner.BS2Runner)
	tpRunner := runner.NewGroup(runner.TPRunner)

	e := lexers.Ensure()
	if e.IsError() {
		log.Fatalf("Command `%s` exited with %d\n", e.Invocation, e.ExitCode)
	}
	// The bs2 parser and assembler were ensured by the lexer.

	runner.RunSuite("test/lex-pass", "lex", "stdout", &lexers, runLex, bless, c, &wg)
	runner.RunSuite("test/parse-pass", "parse", "xml", &parsers, runParse, bless, c, &wg)
	runner.RunSuite("test/asm-pass", "asm", "s", &assembles, runAsm, bless, c, &wg)
	runner.RunSuite("test/asm-pass", "run", "out", &runners, runRun, bless, c, &wg)
	runner.RunSuite("test/example-valid", "parse", "xml", &parsers, runParse, bless, c, &wg)

	runner.RunSuite("test/example-valid", "run", "out", &tpRunner, runRun, bless, c, &wg)

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
			switch result.Status {
			case runner.StatusStart:
				running[result.RunName()] = struct{}{}
			case runner.StatusPass:
				if *verbose {
					fmt.Fprintf(os.Stderr, "PASS %10s %4s %40s (%d running)\n", result.Compiler,
						result.SuiteName, result.TestName, len(running))
				}
				nPass++
				delete(running, result.RunName())
			case runner.StatusFail:
				nFail++
				fmt.Fprintf(os.Stderr, "%s %10s %4s %40s (%d running)\n%s\n", color.RedString("FAIL"), result.Compiler,
					result.SuiteName, result.TestName, len(running), result.Message)
				delete(running, result.RunName())

			}
		case <-done:
			fmt.Fprintf(os.Stderr, "Exiting becuase I thing all are done\n")
			break results
		case <-time.After(10 * time.Second):
			fmt.Fprintf(os.Stderr, "%s", color.RedString("TIMEOUT"))

			for a := range running {
				fmt.Fprintf(os.Stderr, "Still running %s\n", a)
			}
			nFail++ // hack
			//			panic("timeout") // Show other goroutines
			break results
		}
	}

	fmt.Fprintf(os.Stderr, "Realy done for real\n")

	if len(running) != 0 {
		for a := range running {
			fmt.Fprintf(os.Stderr, "Still running %s\n", a)
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

func runRun(a runner.Runner, waccPath string) runner.CommandResult {
	res, exePath := a.Run(waccPath)
	if res.IsError() {
		return res
	}
	inFilePath := runner.WithSuffix(waccPath, "in")
	var inFile *string
	if runner.FileExists(inFilePath) {
		inFile = &inFilePath
	}
	exeRes := runner.RunOutputGet(exePath, inFile)
	// spew.Dump(exeRes)
	res.Output = sanitizeOutput(exeRes.Output)
	res.ExitCode = exeRes.ExitCode
	return res
}

var ptrRe = regexp.MustCompile("0x[0-9a-fA-F]{8,16}")

func sanitizeOutput(s string) string {
	return ptrRe.ReplaceAllLiteralString(s, "0x{{PTR}}")
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

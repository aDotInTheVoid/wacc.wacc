package runner

import (
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
	"sync"
)

func RunSuite[C Compiler](suitePath string,
	suiteName string,
	out_ext string,
	compilers *CompilerGroup[C],
	f func(C, string) CommandResult,
	bless bool,
	c chan TestResult,
	wg *sync.WaitGroup) {

	filepath.Walk(suitePath, func(path string, info fs.FileInfo, err error) error {
		if err != nil {
			return err
		} else if info.IsDir() || filepath.Ext(path) != ".wacc" {
			return nil
		}
		send := func(result TestResult) {
			result.SuiteName = suiteName
			c <- result
		}

		wg.Add(1)
		go func() {
			// mu.Lock()
			// defer mu.Unlock()
			if bless {
				send(TestResult{Compiler: compilers.Authoritative.Name(), TestName: path, Status: StatusStart})

				output := f(compilers.Authoritative, path)
				result := TestResult{TestName: path, Compiler: compilers.Authoritative.Name()}
				if output.IsError() {
					result.Status = StatusFail
					result.Message = output.Error
					send(result)
				} else {
					result.Status = StatusPass
					os.WriteFile(WithSuffix(path, out_ext), []byte(output.Output), 0644)
					send(result)
				}
			} else {
				send(TestResult{Compiler: compilers.Authoritative.Name(), TestName: path, Status: StatusStart})

				send(doRun(compilers.Authoritative, path, out_ext, f))
				for _, comp := range compilers.NonAuthoritative {
					send(TestResult{Compiler: comp.Name(), TestName: path, Status: StatusStart})

					send(doRun(comp, path, out_ext, f))
				}
			}
			wg.Done()
		}()
		return nil
	})
}

var mu sync.Mutex

func doRun[C Compiler](comp C, path string, out_ext string, f func(C, string) CommandResult) TestResult {
	// mu.Lock()
	// defer mu.Unlock()
	r := f(comp, path)
	result := TestResult{TestName: path, Compiler: comp.Name()}
	if r.IsError() {
		result.Status = StatusFail
		result.Message = makeMessage(&r)
		// TODO: Set message
		return result
	}
	outFile := WithSuffix(path, out_ext)
	expectedOut, err := os.ReadFile(outFile)
	if err != nil {
		result.Status = StatusFail
		result.Message = fmt.Sprintf("Cannot read output file: %s", err)
		return result
	}
	if string(expectedOut) == r.Output {
		result.Status = StatusPass
	} else {
		result.Status = StatusFail
		result.Message = fmt.Sprintf("Output mismatch: expected ---\n%s\n--- got ---\n%s\n---", expectedOut, r.Output)

	}
	return result
}

func makeMessage(r *CommandResult) string {
	out := fmt.Sprintf("Command `%s` exited with %d\n", r.Invocation, r.ExitCode)
	stderr := strings.TrimSpace(r.Error)
	stdout := strings.TrimSpace(r.Output)

	if stdout != "" && stderr != "" {
		out += fmt.Sprintf("--- stdout ---\n%s\n--- stderr ---\n%s\n---", stdout, stderr)
	} else if stdout != "" {
		out += fmt.Sprintf("--- stdout ---\n%s\n---", stdout)
	} else if stderr != "" {
		out += fmt.Sprintf("--- stderr ---\n%s\n---", stderr)
	}

	return out
}

package runner

import (
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
	"sync"
)

var mu sync.Mutex

func RunSuite[C Compiler](suiteName string,
	out_ext string,
	compilers *CompilerGroup[C],
	f func(C, string) CommandResult,
	bless bool,
	c chan TestResult,
	wg *sync.WaitGroup) {

	filepath.Walk(suiteName, func(path string, info fs.FileInfo, err error) error {
		if err != nil {
			return err
		} else if info.IsDir() || filepath.Ext(path) != ".wacc" {
			return nil
		}
		wg.Add(1)
		go func() {
			if bless {
				output := f(compilers.Authoritative, path)
				result := TestResult{TestName: path, Compiler: compilers.Authoritative.Name()}
				if output.IsError() {
					result.Status = StatusFail
					result.Message = output.Error
					c <- result
				} else {
					result.Status = StatusPass
					os.WriteFile(withSuffix(path, out_ext), []byte(output.Output), 0644)
					c <- result
				}
			} else {
				c <- doRun(compilers.Authoritative, path, out_ext, f)
				for _, comp := range compilers.NonAuthoritative {
					c <- doRun(comp, path, out_ext, f)
				}
			}
			wg.Done()
		}()
		return nil
	})
}

func doRun[C Compiler](comp C, path string, out_ext string, f func(C, string) CommandResult) TestResult {
	r := f(comp, path)
	result := TestResult{TestName: path, Compiler: comp.Name()}
	if r.IsError() {
		result.Status = StatusFail
		result.Message = makeMessage(&r)
		// TODO: Set message
		return result
	}
	outFile := withSuffix(path, out_ext)
	c, err := os.ReadFile(outFile)
	if err != nil {
		result.Status = StatusFail
		result.Message = fmt.Sprintf("Cannot read output file: %s", err)
		return result
	}
	if string(c) == r.Output {
		result.Status = StatusPass
	} else {
		result.Status = StatusFail
		result.Message = fmt.Sprintf("Output mismatch: expected ---\n%s\n---, got ---\n%s\n---", r.Output, c)

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

func withSuffix(path string, newExt string) string {
	ext := filepath.Ext(path)
	return path[:len(path)-len(ext)] + "." + newExt
}

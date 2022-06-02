package runner

import (
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"sync"
)

func RunSuite[C Compiler](suiteName string,
	out_ext string,
	comillers *CompilerGroup[C],
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
				output := f(comillers.Authoritative, path)
				result := TestResult{TestName: path, Compiler: comillers.Authoritative.Name()}
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
				c <- doRun(comillers.Authoritative, path, out_ext, f)
				for _, comp := range comillers.NonAuthoritative {
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
		result.Message = "Output mismatch" // TODO: Give a diff
	}
	return result
}

func withSuffix(path string, newExt string) string {
	ext := filepath.Ext(path)
	return path[:len(path)-len(ext)] + "." + newExt
}

package runner

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"os/exec"
	"strings"
)

func RunBuildCmd(name string, args ...string) CommandResult {
	invocation := fmt.Sprintf("%s %s", name, strings.Join(args, " "))

	fmt.Fprintln(os.Stderr, invocation)

	cmd := exec.Command(name, args...)
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	cmd.Stdin = os.Stdin
	err := cmd.Run()
	if err != nil {
		// TODO: We don't have stderr/stdout here, because we sent them to os.Stdout
		if exitError, ok := err.(*exec.ExitError); ok {
			return CommandResult{
				Invocation: invocation,
				ExitCode:   exitError.ProcessState.ExitCode(),
			}
		}

		return CommandResult{
			Invocation: invocation,
			Error:      err.Error(),
			ExitCode:   1,
		}
	}

	return CommandResult{
		Invocation: invocation,
		ExitCode:   0,
	}
}

func RunOutputGet(compiller_path string, stdin_path *string, args ...string) CommandResult {
	var stderr bytes.Buffer
	var stdout bytes.Buffer

	invocation := fmt.Sprintf("%s %s", compiller_path, strings.Join(args, " "))
	if stdin_path != nil {
		invocation += " < " + *stdin_path
	}
	result := CommandResult{Invocation: invocation}

	cmd := exec.Command(compiller_path, args...)
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	if stdin_path != nil {
		file, err := os.Open(*stdin_path)
		if err != nil {
			result.Error = fmt.Sprint("Cannot open file: ", stdin_path, ": ", err)
			result.ExitCode = 1
			return result
		}

		fbuf := bufio.NewReader(file)
		cmd.Stdin = fbuf

	}

	err := cmd.Run()
	status := 0
	if err, ok := err.(*exec.ExitError); ok {
		status = err.ProcessState.ExitCode()
	}
	result.ExitCode = status
	result.Output = stdout.String()
	result.Error = stderr.String()
	return result
}

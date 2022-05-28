package runner

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"os/exec"
)

func RunOutputGet(compiller_path string, stdin_path *string, args ...string) Result {
	var stderr bytes.Buffer
	var stdout bytes.Buffer

	cmd := exec.Command(compiller_path, args...)
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	if stdin_path != nil {
		file, err := os.Open(*stdin_path)
		Must(err)
		fbuf := bufio.NewReader(file)
		cmd.Stdin = fbuf

	}

	err := cmd.Run()
	status := 0
	if err, ok := err.(*exec.ExitError); ok {
		status = err.ProcessState.ExitCode()
	}
	return Result{
		Stdout:     stdout.String(),
		Stderr:     stderr.String(),
		StatusCode: status,
	}

}

func RunBuildCmd(dir string, name string, args ...string) error {
	as := []any{name}
	for _, a := range args {
		as = append(as, a)
	}

	fmt.Println(as...)
	cmd := exec.Command(name, args...)
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	cmd.Dir = dir
	return cmd.Run()
}

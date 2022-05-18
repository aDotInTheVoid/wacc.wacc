package runner

import (
	"bufio"
	"bytes"
	"log"
	"os"
	"os/exec"
)

type Output struct {
	Stdout string
	Stderr string
	Status int
}

func RunOutputGet(compiller_path string, file_path string) *Output {
	file, err := os.Open(file_path)
	Must(err)
	fbuf := bufio.NewReader(file)

	var stderr bytes.Buffer
	var stdout bytes.Buffer

	cmd := exec.Command(compiller_path, file_path)
	cmd.Stdin = fbuf
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	err = cmd.Run()
	status := 0
	if err, ok := err.(*exec.ExitError); ok {
		status = err.ProcessState.ExitCode()
	}
	return &Output{
		Stdout: stdout.String(),
		Stderr: stderr.String(),
		Status: status,
	}

}

func RunBuild(dir string, name string, args ...string) {
	cmd := exec.Command(name, args...)
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	cmd.Dir = dir
	err := cmd.Run()
	if err != nil {
		log.Fatal("Failed to run command:", err)
	}
}
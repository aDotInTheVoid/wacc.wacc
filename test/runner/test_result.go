package runner

import "fmt"

type Status int

const (
	StatusPass Status = iota
	StatusFail
	StatusStart
)

type TestResult struct {
	Status    Status
	TestName  string
	SuiteName string
	Compiler  string
	Message   string
}

func (t *TestResult) RunName() string {
	return fmt.Sprintf("%s %s %s", t.Compiler, t.SuiteName, t.TestName)
}

func (t *TestResult) IsError() bool {
	return t.Status == StatusFail
}

package runner

type Status int

const (
	StatusPass Status = iota
	StatusFail
)

type TestResult struct {
	Status   Status
	TestName string
	Compiler string
	Message  string
}

func (t *TestResult) IsError() bool {
	return t.Status == StatusFail
}

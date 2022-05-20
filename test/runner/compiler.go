package runner

type Compiler interface {
	Ensure() error
	Lex(path string) Result
	Name() string
}

type Result struct {
	StatusCode int
	Stdout     string
	Stderr     string
}

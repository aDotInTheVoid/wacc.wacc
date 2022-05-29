package runner

type Compiler interface {
	Ensure() error
	Lex(path string) Result
	Assemble(path string) Result
	Name() string
	Parse(path string) Result
}

type Result struct {
	StatusCode int
	Stdout     string
	Stderr     string
}

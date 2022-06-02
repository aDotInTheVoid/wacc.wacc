package runner

type Compiler interface {
	Name() string
	Ensure() CommandResult
}

type Lexer interface {
	Compiler
	Lex(path string) CommandResult
}

type Parser interface {
	Compiler
	Parse(path string) CommandResult
}

type Assembler interface {
	Compiler
	Assemble(path string) CommandResult
}

type Runner interface {
	Compiler
	// the status of building, and the path to the exe
	Run(path string) (CommandResult, string)
}

type CompilerGroup[C Compiler] struct {
	Authoritative    C
	NonAuthoritative []C
}

func NewGroup[C Compiler](auth C, nonAuth ...C) CompilerGroup[C] {
	return CompilerGroup[C]{auth, nonAuth}
}

func (c *CompilerGroup[C]) Ensure() CommandResult {
	r := c.Authoritative.Ensure()
	if r.IsError() {
		return r
	}
	for _, na := range c.NonAuthoritative {
		r = na.Ensure()
		if r.IsError() {
			break
		}
	}
	return r
}

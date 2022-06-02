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

type CompilerGroup[C Compiler] struct {
	Authoritative    C
	NonAuthoritative []C
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

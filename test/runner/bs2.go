package runner

import (
	"sync"
)

type bs2 struct {
	mu sync.Mutex
}

func (*bs2) Name() string {
	return "bs2"
}

func (b *bs2) Ensure() CommandResult {
	b.mu.Lock()
	defer b.mu.Unlock()

	if !DirExists("bs2/_build/test") {
		c := RunBuildCmd("meson", "setup", "bs2/_build/test", "bs2")
		if c.IsError() {
			return c
		}
	}
	return RunBuildCmd("ninja", "-C", "bs2/_build/test")
}

func (*bs2) Lex(path string) CommandResult {
	return RunOutputGet("bs2/_build/test/bs2", nil, "lex", path)
}
func (*bs2) Parse(path string) CommandResult {
	return RunOutputGet("bs2/_build/test/bs2", nil, "parse", path)
}

// Assemble implements Assembler
func (*bs2) Assemble(path string) CommandResult {
	return RunOutputGet("bs2/_build/test/bs2", nil, "asm", path)
}

// Run implements Runner
func (*bs2) Run(path string) (CommandResult, string) {
	almostExeName := WithSuffix(path, "")
	exeName := "_build/bs2/" + almostExeName[:len(almostExeName)-1]
	cr := RunOutputGet("make", nil, exeName)
	return cr, exeName
}

var thebs2 bs2 = bs2{}
var BS2Lexer Lexer = &thebs2
var BS2Parser Parser = &thebs2
var BS2Assembler Assembler = &thebs2
var BS2Runner Runner = &thebs2

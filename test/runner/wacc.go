package runner

import (
	"path/filepath"
)

type waccLexer struct {
	path string
}

func (w *waccLexer) Name() string {
	return filepath.Base(w.path)
}

func (w *waccLexer) Ensure() CommandResult {
	return RunBuildCmd("make", w.path)
}

// Lex implements Lexer
func (w *waccLexer) Lex(path string) CommandResult {
	return RunOutputGet(w.path, &path)
}

var WaccBs2Lexer Lexer = &waccLexer{path: "_build/wacc-lex-bs2"}
var WaccTpLexer Lexer = &waccLexer{path: "_build/wacc-lex-tp"}

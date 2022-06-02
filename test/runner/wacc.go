package runner

import (
	"path/filepath"
	"sync"
)

type waccLexer struct {
	mu   sync.Mutex
	path string
}

// Name implements Lexer
func (w *waccLexer) Name() string {
	return filepath.Base(w.path)
}

// Ensure implements Lexer
func (w *waccLexer) Ensure() CommandResult {
	w.mu.Lock()
	defer w.mu.Unlock()
	return RunBuildCmd("make", w.path)
}

// Lex implements Lexer
func (w *waccLexer) Lex(path string) CommandResult {
	return RunOutputGet(w.path, &path)
}

var WaccBs2Lexer Lexer = &waccLexer{path: "_build/wacc-bs2"}
var WaccTpLexer Lexer = &waccLexer{path: "_build/wacc-tp"}

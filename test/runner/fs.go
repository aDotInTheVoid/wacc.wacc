package runner

import (
	"os"
	"path/filepath"
)

func DirExists(name string) bool {
	s, err := os.Stat(name)
	if err != nil {
		return false
	}
	return s.IsDir()
}

func FileExists(name string) bool {
	s, err := os.Stat(name)
	if err != nil {
		return false
	}
	return !s.IsDir()
}

func WithSuffix(path string, newExt string) string {
	ext := filepath.Ext(path)
	return path[:len(path)-len(ext)] + "." + newExt
}

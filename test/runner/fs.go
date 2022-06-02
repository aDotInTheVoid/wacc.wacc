package runner

import "os"

func DirExists(name string) bool {
	s, err := os.Stat(name)
	if err != nil {
		return false
	}
	return s.IsDir()
}

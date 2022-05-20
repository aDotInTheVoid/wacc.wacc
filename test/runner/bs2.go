package runner

type BS2 struct{}

var _ Compiler = BS2{}

func (BS2) Ensure() error {
	if !DirExists("../bs2/_build/test") {
		err := RunBuildCmd("../bs2", "meson", "_build/test")
		if err != nil {
			return err
		}
	}
	return RunBuildCmd("../bs2", "ninja", "-C", "_build/test")
}

func (BS2) Lex(path string) Result {
	panic("unimplemented")
}

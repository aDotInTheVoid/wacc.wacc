package runner

type bs2 struct{}

var BS2 Compiler = bs2{}

func (bs2) Ensure() error {
	if !DirExists("../bs2/_build/test") {
		err := RunBuildCmd("../bs2", "meson", "_build/test")
		if err != nil {
			return err
		}
	}
	return RunBuildCmd("../bs2", "ninja", "-C", "_build/test")
}

func (bs2) Lex(path string) Result {
	return RunOutputGet("../bs2/_build/test/bs2", nil, "lex", path)
}

func (bs2) Parse(path string) Result {
	return RunOutputGet("../bs2/_build/test/bs2", nil, "parse", path)
}

// Assemble implements Compiler
func (bs2) Assemble(path string) Result {
	return RunOutputGet("../bs2/_build/test/bs2", nil, "asm", path)
}

func (bs2) Name() string {
	return "bs2"
}

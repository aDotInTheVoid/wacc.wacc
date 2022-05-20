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
	r := RunOutputGet("../bs2/_build/test/bs2", path)
	return Result{
		r.Status,
		r.Stdout,
		r.Stderr,
	}

}

func (bs2) Name() string {
	return "bs2"
}

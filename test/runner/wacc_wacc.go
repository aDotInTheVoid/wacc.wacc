package runner

type WaccWacc struct{}

var _ Compiler = WaccWacc{}

func (WaccWacc) Ensure() error {
	return RunBuildCmd("..", "make", "_build/wacc")
}

func (WaccWacc) Lex(path string) Result {
	r := RunOutputGet("../_build/wacc", path)
	return Result{
		r.Status,
		r.Stdout,
		r.Stderr,
	}
}

func (WaccWacc) Name() string {
	return "wacc.wacc"
}

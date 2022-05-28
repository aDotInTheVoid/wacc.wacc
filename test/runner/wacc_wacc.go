package runner

type WaccWacc struct{}

var _ Compiler = WaccWacc{}

func (WaccWacc) Ensure() error {
	return RunBuildCmd("..", "make", "_build/wacc")
}

func (WaccWacc) Lex(path string) Result {
	return RunOutputGet("../_build/wacc", &path)
}

func (WaccWacc) Parse(path string) Result {
	panic("implement me")
}

func (WaccWacc) Name() string {
	return "wacc.wacc"
}

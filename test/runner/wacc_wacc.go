package runner

type WaccWacc struct{}

var _ Compiler = WaccWacc{}

func (WaccWacc) Ensure() error {
	return RunBuildCmd("..", "make", "_build/wacc")
}

func (WaccWacc) Lex(path string) Result {
	panic("unimplemented")
}

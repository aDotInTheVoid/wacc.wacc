package runner

type WaccToC struct {
}

var _ Compiler = WaccToC{}

func (WaccToC) Ensure() error {
	return RunBuildCmd("..", "make", "_build/tool/tp")
}

func (WaccToC) Lex(path string) Result {
	panic("implement me")
}

func (WaccToC) Parse(string) Result {
	panic("implement me")
}

// Assemble implements Compiler
func (WaccToC) Assemble(path string) Result {
	panic("unimplemented")
}

func (WaccToC) Name() string {
	return "wacc-to-c"
}

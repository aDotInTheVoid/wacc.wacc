package runner

type WaccToC struct {
}

var _ Compiler = WaccToC{}

func (WaccToC) Ensure() error {
	return RunBuildCmd("..", "make", "_build/tool/tp")
}

func (WaccToC) Lex(path string) Result {
	return Result{}
}

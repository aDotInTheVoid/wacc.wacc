package runner

type tp struct{}

func (*tp) Ensure() CommandResult {
	// NOP: Makefile ensures everything
	return CommandResult{
		ExitCode: 0,
	}
}

func (*tp) Name() string {
	return "tp"
}

// Run implements Runner
func (*tp) Run(path string) (CommandResult, string) {
	// TODO: Factor out this common with bs2.Run
	almostExeName := withSuffix(path, "")
	exeName := "_build/tp/" + almostExeName[:len(almostExeName)-1]
	cr := RunOutputGet("make", nil, exeName)
	return cr, exeName
}

var TPRunner Runner = &tp{}

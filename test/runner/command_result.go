package runner

type CommandResult struct {
	Invocation string
	Output     string
	Error      string
	ExitCode   int
}

func (c *CommandResult) IsError() bool {
	return c.ExitCode != 0
}

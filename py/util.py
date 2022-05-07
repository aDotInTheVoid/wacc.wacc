class Generate:
    def __init__(self, name):
        self.name = name

    def __enter__(self):
        self.file = open(f"gen/{self.name}.wacc.in", "w")
        self.guard = f"GEN_{self.name.upper()}_WACC_IN"
        self.file.write(f"#ifndef {self.guard}\n")
        self.file.write(f"#define {self.guard}\n\n")
        return self

    def write(self, s):
        self.file.write(s)

    def __exit__(self, type, value, traceback):
        self.file.write("\n#endif\n")
        self.file.close()


def indent(s: str):
    return "\n".join(f"    {line}" for line in s.split("\n"))

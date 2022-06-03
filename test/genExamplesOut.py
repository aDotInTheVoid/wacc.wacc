#!/usr/bin/env python3
import os
import pathlib
import pprint


def genOut(path):
    with open(path) as f:
        lines = f.readlines()
        try:
            start = lines.index("# Output:\n")
        except ValueError:
            print(f"{path} does not contain `# Output:`")
            return
        output = ""
        for i in lines[start + 1 :]:
            if not i.startswith("#"):
                break
            # breakpoint()
            output += i[2:]

        output = fixup(output)

        with open(pathlib.Path(path).with_suffix(".out"), "w") as f:
            f.write(output)


def fixup(output):
    if "#empty#" in output:
        return ""
    return output.replace("#addrs#", "0x{{PTR}}")


if __name__ == "__main__":
    assert "example-valid" in os.listdir()
    assert "bs2" not in os.listdir()
    for (dirpath, dirnames, filenames) in os.walk("example-valid"):
        for filename in filenames:
            if filename.endswith(".wacc"):
                path = os.path.join(dirpath, filename)
                genOut(path)

import sys

maxlen = 0
numlines = 0
longline = ""


with (open(sys.argv[1])) as f:
    s = f.read()

    for line in s.splitlines():
        numlines += 1
        if len(line) > len(longline):
            longline = line

print(f"{numlines} lines")
print(f"{len(longline)} longest")
print(f"{repr(longline)}")

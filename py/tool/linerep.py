import sys

maxlen = 0
numlines = 0

with (open(sys.argv[1])) as f:
    for line in f.readlines():
        numlines += 1
        maxlen = max(maxlen, len(line))

print(f"{numlines} lines")
print(f"{maxlen} longest")

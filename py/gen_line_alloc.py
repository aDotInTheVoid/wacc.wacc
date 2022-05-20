from util import Generate, comment

NUM_LINES = 3_000
NUM_CHARS = 400

ONE_LINE = "l"
ONE_CHAR = "' '"


def int_div(x, y):
    assert x % y == 0, f"{x} % {y} != 0"
    r = x // y
    assert isinstance(r, int), r
    return r


def main():
    with Generate("line_alloc") as f:
        f.write(comment(f"{NUM_LINES} lines, {NUM_CHARS} chars per line") + "\n")
        #
        # Line allocator
        #
        f.write(comment("Line allocator") + "\n\n")
        f.write(f"\nchar[] alloc_line() is\n")
        f.write(f"char[] r = [\n")

        len_per_char = len(ONE_CHAR) + 1  # +1 for the comma
        chars_per_line = int_div(NUM_CHARS, len_per_char)
        lines_of_chars = len_per_char  # Always true
        # with trailing comma
        for _ in range(lines_of_chars - 1):
            for _ in range(chars_per_line):
                f.write(ONE_CHAR)
                f.write(",")
            f.write("\n")
        # Final line cant have trailing comma
        f.write(",".join(ONE_CHAR for _ in range(chars_per_line)))
        f.write("\n];\nreturn r\nend\n")

        #
        # Lines allocator
        #
        f.write(
            comment("Lines allocator. l is the empty (non final) sentinal") + "\n\n"
        )
        f.write("char[][] alloc_lines(char[] l) is\n")
        f.write("char[][] r = [\n")

        len_per_line = len(ONE_LINE) + 1  # +1 for the comma
        lines_per_line = int_div(NUM_CHARS, len_per_line)
        lines_of_lines = int_div(NUM_LINES, lines_per_line)
        # with trailing comma
        for _ in range(lines_of_lines - 1):
            for _ in range(lines_per_line):
                f.write(ONE_LINE)
                f.write(",")
            f.write("\n")
        # Final line cant have trailing comma
        f.write(",".join(ONE_LINE for _ in range(lines_per_line)))
        f.write("\n];\nreturn r\nend\n")

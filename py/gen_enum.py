from dataclasses import dataclass
from util import Generate, indent


@dataclass
class Enum:
    name: str
    prefix: str
    opts: list[str]


def gen_bsearch(f: list[tuple[int, str]]):
    match f:
        case [(idx, name)]:
            return f"if __e == {idx} then return \"{name}\" else skip fi"
        case _:
            mid = len(f)//2
            pivot = f[mid][0]
            less = gen_bsearch(f[:mid])
            greater = gen_bsearch(f[mid:])
            return f"if __e < {pivot} then\n" + indent(less) + "\nelse\n" + indent(greater) + "\nfi"


def gen_enum(e: Enum, i: int):
    with Generate(e.name) as f:
        name = e.name.upper()
        prefix = e.prefix.upper()

        f.write(f"\n#define {name} int\n\n")

        vals = []

        for idx, opt in enumerate(e.opts):
            eno = i * 1000 + idx
            vals.append((eno, opt))
            f.write(f"#define {prefix}_{opt.upper()} {eno}\n")

        f.write(f"string {e.name}_str({name} __e) is\n")
        f.write(indent(gen_bsearch(vals)))
        f.write("    ; exit 1\n")
        f.write("end\n")


def main():
    for idx, e in enumerate(
        [
            Enum(
                "token_type",
                "token",
                [
                    "LEFT_PAREN",
                    "RIGHT_PAREN",
                    "LEFT_BRACE",
                    "RIGHT_BRACE",
                    "COMMA",
                    "DOT",
                    "MINUS",
                    "PLUS",
                    "SEMICOLON",
                    "SLASH",
                    "STAR",
                    "BANG",
                    "BANG_EQUAL",
                    "EQUAL",
                    "EQUAL_EQUAL",
                    "GREATER",
                    "GREATER_EQUAL",
                    "LESS",
                    "LESS_EQUAL",
                    "IDENTIFIER",
                    "STRING",
                    "NUMBER",
                    "AND",
                    "CLASS",
                    "ELSE",
                    "FALSE",
                    "FOR",
                    "FUN",
                    "IF",
                    "NIL",
                    "OR",
                    "PRINT",
                    "RETURN",
                    "SUPER",
                    "THIS",
                    "TRUE",
                    "VAR",
                    "WHILE",
                    "ERROR",
                    "EOF",
                ],
            )
        ]
    ):
        gen_enum(e, idx)

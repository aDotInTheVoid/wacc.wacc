from dataclasses import dataclass
from util import Generate, indent


@dataclass
class Enum:
    name: str
    prefix: str
    opts: list[str]


def gen_bsearch_tree(f):
    match f:
        case [(key, value)]:
            return ("=", key, value)
        case _:
            mid = len(f) // 2
            pivot = f[mid][0]
            less = gen_bsearch_tree(f[:mid])
            greater = gen_bsearch_tree(f[mid:])
            return ("<", pivot, less, greater)


def gen_bsearch(tree):
    match tree:
        case ("=", key, value):
            return f'if __e == {key} then return "{value}" ENDIF'
        case ("<", pivot, less, greater):
            return f"if __e < {pivot} then\n{indent(gen_bsearch(less))}\nelse\n{indent(gen_bsearch(greater))}\nfi"
        case _:
            raise Exception("invalid tree", tree)


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
        f.write(indent(gen_bsearch(gen_bsearch_tree(vals))))
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

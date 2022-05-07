from dataclasses import dataclass
from util import Generate


@dataclass
class Enum:
    name: str
    prefix: str
    opts: list[str]


def gen_enum(e: Enum, i: int):
    with Generate(e.name) as f:
        name = e.name.upper()
        prefix = e.prefix.upper()

        f.write(f"\n#define {name} int\n\n")

        for idx, opt in enumerate(e.opts):
            eno = i * 1000 + idx
            f.write(f"#define {prefix}_{opt.upper()} {eno}\n")


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

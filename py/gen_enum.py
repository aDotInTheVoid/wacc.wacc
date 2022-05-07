from dataclasses import dataclass


@dataclass
class Enum:
    name: str
    prefix: str
    opts: list[str]


def gen_enum(e: Enum, i: int):
    with open(f"gen/{e.name}.wacc.in", "w") as f:
        guard_name = f"gen_{e.name}_wacc_in".upper()
        f.write(f"#ifndef {guard_name}\n")
        f.write(f"#define {guard_name}\n")

        name = e.name.upper()
        prefix = e.prefix.upper()

        f.write(f"\n#define {name} int\n\n")

        for idx, opt in enumerate(e.opts):
            eno = i * 1000 + idx
            f.write(f"#define {prefix}_{opt.upper()} {eno}\n")

        f.write("\n#endif\n")


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

from dataclasses import dataclass
import pprint
from util import Generate, indent
from gen_trie import KEYWORDS, PUNCT


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
        enogen = lambda x: i * 1000 + x

        # TODO: Comment
        f.write(f"// enum {e.name} (base={i}) {{\n")
        for idx, opt in enumerate(e.opts):
            f.write(f"//     {opt} = {enogen(idx)},\n")
        f.write(f"// }}\n")

        name = e.name.upper()
        prefix = e.prefix.upper()

        f.write(f"\n#define {name} int\n\n")

        vals = []

        for idx, opt in enumerate(e.opts):
            eno = enogen(idx)
            vals.append((eno, opt))
            f.write(f"#define {prefix}_{opt.upper()} {eno}\n")

        f.write(f"string {e.name}_str({name} __e) is\n")
        # TODO: Look into using an array here.
        f.write(indent(gen_bsearch(gen_bsearch_tree(vals))))
        f.write("    ; exit 1\n")
        f.write("end\n")


def main():
    # TODO: Str lit and char lit
    token_names = ["identifier", "number", "eof"]
    for i in KEYWORDS:
        token_names.append(i)
    for _, i in PUNCT:
        token_names.append(i)
    assert len(token_names) == len(set(token_names))

    for idx, e in enumerate([Enum("token_type", "token", token_names)]):
        gen_enum(e, idx)

from util import Generate, indent

PUNCT = [
    ("(", "lparen"),
    (")", "rparen"),
    ("=", "assign"),
    (";", "semi"),
    (",", "comma"),
    ("[", "lsquare"),
    ("]", "rsquare"),
    ("!", "not"),
    ("-", "minus"),
    ("*", "times"),
    ("/", "div"),
    ("%", "mod"),
    ("+", "plus"),
    (">,", "gt"),
    (">=", "ge"),
    ("<", "lt"),
    ("<=", "le"),
    ("==", "eq"),
    ("!=", "ne"),
    ("&&", "and"),
    ("||", "or"),
]

KEYWORDS = [
    "begin",
    "bool",
    "call",
    "char",
    "chr",
    "do",
    "done",
    "else",
    "end",
    "exit",
    "false",
    "fi",
    "free",
    "fst",
    "if",
    "int",
    "is",
    "len",
    "newpair",
    "null",
    "ord",
    "pair",
    "print",
    "println",
    "read",
    "return",
    "skip",
    "snd",
    "string",
    "then",
    "true",
    "while",
]


def first_diff(a, b):
    assert a != b
    for i in range(min(len(a), len(b))):
        if a[i] != b[i]:
            return i
    return None


# Return the first charecter that the words have different
def same_up_to(words):
    i = 0
    assert len(words) > 0
    minlen = min(len(w) for w in words)
    while i < minlen:
        if len(set(w[i] for w in words)) != 1:
            return i
        i += 1
    return None


def _deltas():
    yield 0
    i = 1
    while True:
        yield i
        yield -i
        i = i + 1


def pick_mid_counds(diffs: list[str]) -> int:
    assert len(set(diffs)) > 1
    best_mid = len(diffs) // 2

    for d in _deltas():
        mid = best_mid + d
        lo_boundry = diffs[mid - 1]
        hi_boundry = diffs[mid]
        if lo_boundry != hi_boundry:
            return mid
    raise Exception(f"Could not find midpoint of {diffs}")


# (idx, char, low, high): if s[idx] <= char, then low, else high
# string: if s == string then KW(string), else s
# (int, eq, neq): if len(s) <= int then eq else neq
# (int, those) if len(s) == int then those else None
# TODO: Some of these len checks are redundant, if we know the rang
def build_trie(words):
    words = sorted(words)
    words = sorted(words, key=len)
    return _build_trie(words)


def _all_same_len(words):
    l0 = len(words[0])
    for w in words[1:]:
        if len(w) != l0:
            return False
    return True


# pre: words is sorted by length, then lexicographically
def _build_trie(words):
    if len(words) == 1:
        return words[0]
    elif len(words) == 0:
        raise Exception("Empty list")
    elif _all_same_len(words):
        return len(words[0]), _build_trie_alpha(words)
    mid = pick_mid_counds([len(i) for i in words])
    lows = words[:mid]
    highs = words[mid:]
    pivot = len(lows[-1])
    return (pivot, _build_trie(lows), _build_trie(highs))


# pre: words sorted lexographically, all same lenght
def _build_trie_alpha(words):
    if len(words) == 1:
        return words[0]

    check_idx = same_up_to(words)
    mid = pick_mid_counds([w[check_idx] for w in words])

    lows = words[:mid]
    highs = words[mid:]
    check_char = lows[-1][check_idx]

    return (check_idx, check_char, _build_trie_alpha(lows), _build_trie_alpha(highs))


def gen_trie_code(trie, vals):
    match trie:
        case (int(l), leq, gt):
            leqtext = gen_trie_code(leq, vals)
            gttext = gen_trie_code(gt, vals)
            return f"if lenn <= {l} then\n{indent(leqtext)}\nelse\n{indent(gttext)}\nfi"
        case (int(l), when):
            whentext = gen_trie_code(when, vals)
            return f"if lenn == {l} then\n{indent(whentext)}\nENDIF"
        case (int(l), str(expected), leq, gt):
            leqtext = gen_trie_code(leq, vals)
            gttext = gen_trie_code(gt, vals)
            return f"if str[start + {l}] <= '{expected}' then\n{indent(leqtext)}\nelse\n{indent(gttext)}\nfi"
        case str(s):
            l1 = "char[] exp = [" + ", ".join(f"'{c}'" for c in s) + "]"
            l2 = "bool eq =  call streq(str, start, lenn, exp)"
            l3 = "free exp"
            l4 = f"if eq then return {vals[s]} ENDIF"
            return ";\n".join([l1, l2, l3, l4])


def gen_trie(name, includes, ret_ty, vals, default):
    with Generate(name) as f:
        for i in includes:
            f.write(f'#include "{i}.wacc.in"\n')
        f.write("\n")

        f.write(f"{ret_ty} {name}(char[] str, int start, int lenn) is\n")

        keynames = list(vals.keys())
        trie = build_trie(keynames)

        f.write(indent(gen_trie_code(trie, vals)))

        f.write(f" ;\n    return {default}\n")
        f.write("end\n")


def main():
    gen_trie(
        name="identifier_kind",
        includes=["token_type"],
        ret_ty="TOKEN_TYPE",
        vals={k: f"TOKEN_{k.upper()}" for k in KEYWORDS},
        default="TOKEN_IDENTIFIER",
    )
    gen_trie(
        name="punct_kind",
        includes=["token_type"],
        ret_ty="TOKEN_TYPE",
        vals={k[0]: v for k, v in PUNCT},
        default="XXXTODO",
    )

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


def pick_mid_counds(diffs: list[str]) -> int:
    assert len(set(diffs)) > 1
    best_mid = len(diffs) // 2

    delta = [0, 1, -1, 2, -2, 3, -3]  # TODO: Expand
    for d in delta:
        mid = best_mid + d
        lo_boundry = diffs[mid - 1]
        hi_boundry = diffs[mid]
        if lo_boundry != hi_boundry:
            return mid
    raise Exception("Could not find midpoint")


# (idx, char, low, high): if s[idx] <= char, then low, else high
# string: if s == string then KW(string), else s
# (char, eq, neq): if s[0] == char then eq  else neq
# (int, eq, neq): if len(s) == int then eq else neq
def gen_trie(words):
    if len(words) == 1:
        return words[0]
    unique_to = same_up_to(words)
    if unique_to is None:
        # Degenerate case, eg "do", and "done"
        assert len(words) == 2  # Not fully general, but should be good enough
        return _trie_degen(words[0], words[1])
    diffs = [w[unique_to] for w in words]
    mid = pick_mid_counds(diffs)
    return _gen_trie_split(words, mid)


def search(word, trie):
    match trie:
        case (int(idx), str(char), low, high):
            if word[idx] <= char:
                return search(word, low)
            else:
                return search(word, high)
        case str(s):
            if word == s:
                return s
            else:
                return None
        case (str(char), eq, neq):
            if word[0] == char:
                return search(word, eq)
            else:
                return search(word, neq)
        case (int(l), eq, neq):
            if len(word) == l:
                return search(word, eq)
            else:
                return search(word, neq)
        case _:
            raise Exception(f"Unknown trie node: {trie}")


def _trie_degen(a, b):
    assert a.startswith(b) or b.startswith(a)
    assert a != b
    return (len(a), a, b)


def _gen_trie_split(words, mid):
    lows = words[:mid]
    highs = words[mid:]

    assert len(lows) >= 1
    assert len(highs) >= 1

    low_max = lows[-1]
    high_min = highs[0]

    check_idx = first_diff(low_max, high_min)
    if check_idx is None:
        # degenerate case, eg "do", and "done"
        first = low_max[0]
        normals = lows[:-1] + highs[1:]

        for i in normals:
            assert i[0] != first  # Not garenteed, so this won't always work
        if normals:
            return (first, _trie_degen(low_max, high_min), gen_trie(normals))
        else:
            return _trie_degen(low_max, high_min)

    check_char = low_max[check_idx]
    return (check_idx, check_char, gen_trie(lows), gen_trie(highs))

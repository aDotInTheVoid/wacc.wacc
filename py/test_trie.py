from gen_trie import KEYWORDS, first_diff, build_trie, same_up_to


def test_keyword_sorted_and_unique():
    assert len(KEYWORDS) == len(set(KEYWORDS))
    assert KEYWORDS == sorted(KEYWORDS)


def test_first_diff():
    assert first_diff("abc", "abd") == 2
    assert first_diff("a", "b") == 0


def search(word, trie):
    print(word, trie)
    match trie:
        case (int(l), leq, gt):
            if len(word) <= l:
                return search(word, leq)
            else:
                return search(word, gt)
        case (int(l), those):
            if len(word) == l:
                return search(word, those)
            else:
                return None
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
        case _:
            raise Exception(f"Unknown trie node: {trie}")


def close_to(w):
    yield w[:-1] + chr(ord(w[-1]) + 1)
    yield w[:-1] + chr(ord(w[-1]) - 1)
    yield chr(ord(w[0]) - 1) + w[1:]
    yield chr(ord(w[0]) + 1) + w[1:]
    yield w[:-1]
    yield w[1:]
    yield w + "a"
    yield "The fast and the furious presents: " + w


def do_search_test(words):
    trie = build_trie(words)
    wset = set(words)
    for w in words:
        assert search(w, trie) == w
        for walt in close_to(w):
            if walt not in wset:
                assert search(walt, trie) is None


def test_same_up_to():
    assert same_up_to(["a", "b", "c"]) == 0
    assert same_up_to(["cat", "cow"]) == 1
    assert same_up_to(["cat", "cow", "dog"]) == 0
    assert same_up_to(["123a1", "123a2", "123b1"]) == 3


def test_gen_trie():
    assert build_trie(["a", "b"]) == (1, (0, "a", "a", "b"))
    assert build_trie(["chr", "do", "done", "else"]) == (
        3,
        (2, "do", "chr"),
        (4, (0, "d", "done", "else")),
    )
    assert build_trie(["begin", "call", "char", "do", "done"]) == (
        2,
        "do",
        (4, (4, (0, "c", (1, "a", "call", "char"), "done")), "begin"),
    )
    assert build_trie(["aa", "ab", "ac", "daax", "daay", "daaz"]) == (
        2,
        (2, (1, "a", "aa", (1, "b", "ab", "ac"))),
        (4, (3, "x", "daax", (3, "y", "daay", "daaz"))),
    )
    assert build_trie(KEYWORDS) == (
        3,
        (
            2,
            (2, (0, "f", (0, "d", "do", "fi"), (1, "f", "if", "is"))),
            (
                3,
                (
                    0,
                    "f",
                    (0, "c", "chr", (0, "e", "end", "fst")),
                    (0, "l", (0, "i", "int", "len"), (0, "o", "ord", "snd")),
                ),
            ),
        ),
        (
            4,
            (
                4,
                (
                    0,
                    "e",
                    (
                        0,
                        "c",
                        (0, "b", "bool", (1, "a", "call", "char")),
                        (0, "d", "done", (1, "l", "else", "exit")),
                    ),
                    (
                        0,
                        "p",
                        (0, "f", "free", (0, "n", "null", "pair")),
                        (0, "s", (0, "r", "read", "skip"), (1, "h", "then", "true")),
                    ),
                ),
            ),
            (
                5,
                (5, (0, "f", (0, "b", "begin", "false"), (0, "p", "print", "while"))),
                (
                    6,
                    (6, (0, "r", "return", "string")),
                    (7, (0, "n", "newpair", "println")),
                ),
            ),
        ),
    )


def test_trie_search():
    # do_search_test(["a", "b"])
    # do_search_test(["chr", "do", "done", "else"])
    # do_search_test(["begin", "call", "char", "do", "done"])
    # do_search_test(["begin", "bool", "call", "char", "chr", "do", "done", "else"])
    do_search_test(KEYWORDS)

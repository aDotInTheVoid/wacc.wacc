from gen_trie import KEYWORDS, first_diff, gen_trie, search, same_up_to


def test_keyword_sorted_and_unique():
    assert len(KEYWORDS) == len(set(KEYWORDS))
    assert KEYWORDS == sorted(KEYWORDS)


def test_first_diff():
    assert first_diff("abc", "abd") == 2
    assert first_diff("a", "b") == 0


def do_search_test(words):
    trie = gen_trie(words)
    for w in words:
        assert search(w, trie) == w


def test_same_up_to():
    assert same_up_to(["a", "b", "c"]) == 0
    assert same_up_to(["cat", "cow"]) == 1
    assert same_up_to(["cat", "cow", "dog"]) == 0
    assert same_up_to(["123a1", "123a2", "123b1"]) == 3


def test_gen_trie():
    assert gen_trie(["a", "b"]) == (0, "a", "a", "b")
    assert gen_trie(["chr", "do", "done", "else"]) == (
        0,
        "d",
        (0, "c", "chr", (2, "do", "done")),
        "else",
    )
    assert gen_trie(["begin", "call", "char", "do", "done"]) == (
        0,
        "c",
        (0, "b", "begin", (1, "a", "call", "char")),
        (2, "do", "done"),
    )
    gen_trie(KEYWORDS)


def test_trie_search():
    do_search_test(["a", "b"])
    do_search_test(["chr", "do", "done", "else"])
    do_search_test(["begin", "call", "char", "do", "done"])
    do_search_test(["begin", "bool", "call", "char", "chr", "do", "done", "else"])
    do_search_test(KEYWORDS)

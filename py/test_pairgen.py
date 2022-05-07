from pairgen import pairgen


def test_1():
    assert pairgen("a") == "a"
    assert pairgen("b") == "b"


def test_2():
    assert pairgen(["a", "b"]) == ("a", "b")
    assert pairgen(["b", "a"]) == ("b", "a")


def test_3():
    assert pairgen(["a", "b", "c"]) == ("c", ("a", "b"))
    assert pairgen(["a", "c", "b"]) == ("b", ("a", "c"))
    assert pairgen(["b", "a", "c"]) == ("c", ("b", "a"))
    assert pairgen(["b", "c", "a"]) == ("a", ("b", "c"))
    assert pairgen(["c", "a", "b"]) == ("b", ("c", "a"))
    assert pairgen(["c", "b", "a"]) == ("a", ("c", "b"))


def test_4():
    assert pairgen(["a", "b", "c", "d"]) == (("a", "c"), ("b", "d"))


def test_16():
    assert pairgen(list(range(16))) == (
        (((0, 2), (13, 15)), ((8, 7), (5, 12))),
        (((11, 1), (6, 14)), ((9, 3), (4, 10))),
    )

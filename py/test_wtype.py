import wtype


def test_str():
    assert str(wtype.Int()) == "int"
    assert f"{wtype.Int()}" == "int"

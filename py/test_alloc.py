from gen_alloc import gen_bsearch


def test_bsearch():
    assert gen_bsearch([10]) == (10, 10, None)
    assert gen_bsearch([10, 20]) == (20, (10, 10, 20), None)
    assert gen_bsearch([10, 20, 30]) == (20, (10, 10, 20), (30, 30, None))
    assert gen_bsearch([10, 20, 30, 40]) == (30, (20, (10, 10, 20), 30), (40, 40, None))
    assert gen_bsearch([10, 20, 30, 40, 50]) == (
        30,
        (20, (10, 10, 20), 30),
        (50, (40, 40, 50), None),
    )

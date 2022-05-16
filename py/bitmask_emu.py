from int_emu import WInt

# TODO: Flesh out and generate tests.
TEST_CLEAR_LOWER = [
    (1, 1, 0),
    (2, 1, 2),
    (2, 2, 0),
    (9, 3, 8),
    (0b1010111, 3, 0b1010000),
    (0b1010111, 4, 0b1010000),
    (0b1010111, 5, 0b1000000),
]
TEST_CLEAR_UPPER = [
    (0x7FFFFFFF, 0, 0x7FFFFFFF),
    (0x7FFFFFFF, 1, 0x3FFFFFFF),
    (0b1111110000000000000001000010010, 0, 0b1111110000000000000001000010010),
    (0b1111110000000000000001000010010, 1, 0b111110000000000000001000010010),
    (0b1111110000000000000001000010010, 2, 0b11110000000000000001000010010),
    (0b1111110000000000000001000010010, 3, 0b1110000000000000001000010010),
    (0b1111110000000000000001000010010, 4, 0b110000000000000001000010010),
    (0b1111110000000000000001000010010, 5, 0b10000000000000001000010010),
    (0b1111110000000000000001000010010, 6, 0b0000000000000001000010010),
]
TEST_POW2 = [
    (0, 1),
    (1, 2),
    (2, 4),
    (30, 2**30),
]
TEST_N_UPPER = [
    (0x7FFFFFFF, 0, 0),
    (0, 0, 0),
    (1, 0, 0),
    (0x7FFFFFFF, 1, 1),
    (0x7FFFFFFF, 2, 3),
    (0x7FFFFFFF, 3, 7),
    (0x7FFFFFFF, 4, 15),
    (0x7AFEBABE, 15, 0x7AFE),
    (0x7AFEBABE, 11, 0x7AF),
    (0x7AFEBABE, 7, 0x7A),
    (0x7AFEBABE, 3, 0x7),
]
TEST_N_LOWER = [
    (0x7FFFFFFF, 0, 0),
    (0, 0, 0),
    (1, 0, 0),
    (0x7FFFFFFF, 1, 1),
    (0x7FFFFFFF, 2, 3),
    (0x7FFFFFFF, 3, 7),
    (0x7FFFFFFF, 4, 15),
    (0x7AFEBABE, 16, 0xBABE),
    (0x7AFEBABE, 12, 0xABE),
    (0x7AFEBABE, 8, 0xBE),
    (0x7AFEBABE, 4, 0xE),
]


def pow2(n: WInt) -> WInt:
    if n > WInt(30):
        raise ValueError("n must be <= 30")
    r = WInt(1)
    while n > WInt(0):
        r = r * WInt(2)
        n -= WInt(1)
    return r


def clear_lower(x, n):
    pt = pow2(n)
    return (x / pt) * pt


def clear_upper(x, n):
    if n == WInt(0):
        return x
    return x - clear_lower(x, WInt(31) - n)


def n_upper(x, n):
    if n == WInt(0):
        return WInt(0)
    pt = pow2(WInt(31) - n)
    return x / pt


def n_lower(x, n):
    if n == WInt(0):
        return 0
    pt = pow2(n)
    return x % pt

from bitmask_emu import clear_lower, clear_upper
import bitmask_emu
from int_emu import WInt


def test_clear_lower():
    for x, n, expected in bitmask_emu.TEST_CLEAR_LOWER:
        assert clear_lower(WInt(x), WInt(n)) == WInt(expected)


def test_pow2():
    for n, expected in bitmask_emu.TEST_POW2:
        assert 2**n == expected
        assert bitmask_emu.pow2(WInt(n)) == WInt(expected)


def test_clear_upper():
    for x, n, expected in bitmask_emu.TEST_CLEAR_UPPER:
        assert clear_upper(WInt(x), WInt(n)) == WInt(expected)


def test_n_upper():
    for x, n, expected in bitmask_emu.TEST_N_UPPER:
        assert bitmask_emu.n_upper(WInt(x), WInt(n)) == WInt(expected)

import pytest
from int_emu import WInt, WaccIntErr
import int_emu


def test_wint_add():
    for a, b, c in int_emu.TEST_ADD:
        assert WInt(a) + WInt(b) == WInt(c)
        assert a + b == c


def test_wint_add_err():
    for a, b in int_emu.TEST_ADD_ERR:
        with pytest.raises(WaccIntErr):
            WInt(a) + WInt(b)


def test_wint_div():
    for a, b, c in int_emu.TEST_DIV:
        assert WInt(a) / WInt(b) == WInt(c)
        assert a // b == c  # Wacc Int division is floor division


def test_wint_div_err():
    for a, b in int_emu.TEST_DIV_ERR:
        with pytest.raises(WaccIntErr):
            WInt(a) / WInt(b)


def test_wint_mod():
    for a, b, c in int_emu.TEST_MOD:
        assert WInt(a) % WInt(b) == WInt(c)
        assert a % b == c


def test_wint_mod_err():
    for a, b in int_emu.TEST_MOD_ERR:
        with pytest.raises(WaccIntErr):
            WInt(a) % WInt(b)

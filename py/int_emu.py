# Emulator for wacc ints.


MIN = -(2**31)
MAX = 2**31 - 1

# TODO: Generate tests from these
# TODO: Flesh out
TEST_ADD = [
    (1, 2, 3),
    (0, 0, 0),
    (-1, 1, 0),
    (MAX, MIN, -1),
    (MIN, MAX, -1),
    (MAX, -1, MAX - 1),
    (MIN, 1, MIN + 1),
]
TEST_ADD_ERR = [
    (MAX, 1),
    (1, MAX),
    (-1, MIN),
    (MIN, -1),
]
TEST_DIV = [
    (1, 2, 0),
    (0, 1, 0),
    (0, MAX, 0),
    (0, MIN, 0),
    (-1, 1, -1),
    (-1, -1, 1),
    (MAX, MIN, -1),
    (MAX, MAX - 1, 1),
    (MAX, MAX - 1, 1),
]
TEST_DIV_ERR = [
    (0, 0),
    (1, 0),
    (100, 0),
    (-32, 0),
    (MIN, 0),
    (MAX, 0),
]
TEST_MOD = [
    (1, 2, 1),
    (0, 1, 0),
    (2, 1, 0),
    (100, 7, 2),
]
TEST_MOD_ERR = [
    (0, 0),
    (1, 0),
    (100, 0),
    (-32, 0),
    (MIN, 0),
    (MAX, 0),
]


class WaccIntErr(Exception):
    pass


class WInt:
    val: int

    def __init__(self, val: int):
        assert isinstance(val, int)
        if val < MIN or val > MAX:
            raise WaccIntErr(f"Value {val} out of range")
        self.val = val

    def __str__(self):
        return str(self.val)

    def __repr__(self):
        return f"WInt({bin(self.val)} {self.val})"

    def __add__(self, other):
        return WInt(self.val + other.val)

    def __sub__(self, other):
        return WInt(self.val - other.val)

    def __mul__(self, other):
        return WInt(self.val * other.val)

    def __truediv__(self, other):
        if other.val == 0:
            raise WaccIntErr("Division by zero")
        return WInt(self.val // other.val)

    def __mod__(self, other):
        if other.val == 0:
            raise WaccIntErr("Modulus by zero")
        return WInt(self.val % other.val)

    def __lt__(self, other):
        return self.val < other.val

    def __le__(self, other):
        return self.val <= other.val

    def __eq__(self, other):
        return self.val == other.val

    def __ne__(self, other):
        return self.val != other.val

    def __gt__(self, other):
        return self.val > other.val

    def __ge__(self, other):
        return self.val >= other.val

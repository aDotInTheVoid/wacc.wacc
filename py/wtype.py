from dataclasses import dataclass


class Type:
    pass


class Int(Type):
    def __str__(self) -> str:
        return "int"


class Bool(Type):
    def __str__(self) -> str:
        return "bool"


class String(Type):
    def __str__(self) -> str:
        return "string"


class Char(Type):
    def __str__(self) -> str:
        return "char"


@dataclass
class Array(Type):
    inner: Type

    def __str__(self) -> str:
        return f"{self.inner}[]"


@dataclass
class Pair(Type):
    left: Type
    right: Type


class EraisedPair(Type):
    pass

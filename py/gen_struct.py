import dataclasses
from pprint import pformat


import wtype
from wtype import Type
from pairgen import pairgen

@dataclasses.dataclass
class StructField:
    name: str
    field: Type


@dataclasses.dataclass
class Struct:
    name: str
    fields: list[StructField]

def indent(s: str):
    return "\n".join(f"    {line}" for line in s.split("\n"))

def print_struct_tree(f):
    match f:
        case (l, r):
            return "[\n" + indent(print_struct_tree(l)) + "\n" + indent(print_struct_tree(r)) + "\n]" 
        case StructField(name, type):
            return f"{name}: {type}"

def comment(s: str):
    return "\n".join(f"// {line}" for line in s.split("\n"))

def nested_pair_name(p):
    match p:
        case ((_,_), (_,_)):
            return "pair(pair, pair)"
        case ((_,_), r):
            return f"pair(pair, {r.field})"
        case (l, (_,_)):
            return f"pair({l.field}, pair)"
        case (l, r):
            return f"pair({l.field}, {r.field})"
        case s:
            return str(s.field)

def gen_ctor(fielding, prefix) -> str:
    match fielding:
        case (l, r):
            lp, rp = "l" + prefix, "r" + prefix
            lc, rc = gen_ctor(l, lp), gen_ctor(r, rp)
            combo = f"{nested_pair_name(fielding)} {prefix} = newpair({lp}, {rp});\n"
            return lc + rc + combo
        case StructField(name, type):
            return f"{type} {prefix} = {name};\n"

def gen_struct(s: Struct):
    with open(f"gen/{s.name}.wacc.in", "w") as f:
        f.write(f"// struct {s.name} {{\n")
        for field in s.fields:
            f.write(f"//     {field.name}: {field.field},\n")
        f.write("// }\n\n")

        fielding = pairgen(s.fields)
        f.write(comment(print_struct_tree(fielding)))

        type_name = f"{s.name}_t".upper()

        f.write(f"\n#define {type_name} {nested_pair_name(fielding)}\n\n")

        f.write(f"{type_name} {s.name}_new(\n")
        for field in s.fields:
            f.write(f"    {field.field} {field.name},\n")
        f.write(") is\n")
        
        f.write(indent(gen_ctor(fielding, "__ctor")))
        f.write("return __ctor\n")

        f.write("end")

        
        

if __name__ == "__main__":
    for s in [
        Struct(
            "lexer",
            [
                StructField("source", wtype.String()),
                StructField("start", wtype.Int()),
                StructField("current", wtype.Int()),
            ],
        )
    ]:
        gen_struct(s)

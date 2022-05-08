import dataclasses
from util import Generate, indent
from wtype import Array


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


def print_struct_tree(f):
    match f:
        case (l, r):
            return (
                "[\n"
                + indent(print_struct_tree(l))
                + "\n"
                + indent(print_struct_tree(r))
                + "\n]"
            )
        case StructField(name, type):
            return f"{name}: {type}"


def comment(s: str):
    return "\n".join(f"// {line}" for line in s.split("\n"))


def nested_pair_name(p):
    match p:
        case ((_, _), (_, _)):
            return "pair(pair, pair)"
        case ((_, _), r):
            return f"pair(pair, {r.field})"
        case (l, (_, _)):
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


# Returns the init of a struct from the pair, and a map of field names to RValues
def gen_init(fielding, prefix):
    match fielding:
        case (l, r):
            cname = "__" + prefix.replace(" ", "").replace("_", "")
            if cname != prefix:
                hereexpr = f"{nested_pair_name(fielding)} {cname} = {prefix};\n"
            else:
                hereexpr = ""
            ltext, lmap = gen_init(l, f"fst {cname}")
            rtext, rmap = gen_init(r, f"snd {cname}")
            return hereexpr + ltext + rtext, lmap | rmap
        case StructField(name, type):
            return f"{type} {name} = {prefix};\n", {name: prefix}


def gen_refresh(fielding, prefix):
    match fielding:
        case (l, r):
            cname = "__" + prefix.replace(" ", "").replace("_", "")
            ltext = gen_refresh(l, f"fst {cname}")
            rtext = gen_refresh(r, f"snd {cname}")
            return ltext + rtext
        case StructField(name, _):
            return f"{name} = {prefix};\n"


def gen_dtor(fielding, prefix):
    match fielding:
        case (l, r):
            lp, rp = "l" + prefix, "r" + prefix
            ltext = f"{nested_pair_name(l)} {lp} = fst {prefix};\n"
            rtext = f"{nested_pair_name(r)} {rp} = snd {prefix};\n"
            free = f"free {prefix};\n"
            return "".join([ltext, rtext, gen_dtor(l, lp), gen_dtor(r, rp), free])
        # TODO: Handle nested arrays
        # TODO: Does freeing a struct always free it's array?
        case StructField(_, Array(_)):
            return f"free {prefix};\n"
        case _:
            return ""


def trail_slash(s: str):
    return " \\\n".join(s.split("\n"))


def gen_struct(s: Struct):
    with Generate(s.name) as f:
        assert (
            len(s.fields) > 1
        ), "Can't have struct with 1 field, as need pair indirection for mutability"
        # Comment describing the struct, C version
        f.write(f"// struct {s.name} {{\n")
        for field in s.fields:
            f.write(f"//     {field.name}: {field.field},\n")
        f.write("// }\n\n")
        # Comment describing the struct, nested pairs
        fielding = pairgen(s.fields)
        f.write(comment(print_struct_tree(fielding)))

        # Typedef macro
        type_name = f"{s.name}_t".upper()
        f.write(f"\n#define {type_name} {nested_pair_name(fielding)}\n\n")

        # Ctor
        f.write(f"{type_name} {s.name}_ctor(\n")
        for idx, field in enumerate(s.fields):
            f.write(
                f"    {field.field} {field.name}"
                + (",\n" if idx != len(s.fields) - 1 else "\n")
            )
        f.write(") is\n")
        f.write(indent(gen_ctor(fielding, "__ctor")))
        f.write("return __ctor\n")
        f.write("end\n\n")

        f.write(f"VOID {s.name}_free({type_name} self) is\n")
        f.write(indent(gen_dtor(fielding, "self")))
        f.write("\nENDV\n\n")

        # Macro for function definition
        f.write(f"#define {s.name.upper()}_FN(__rtype, __fname, ...) \\\n")
        obj_name = "self"  # f"__obj{s.name}"
        f.write(f"    __rtype __fname({type_name} {obj_name} __VA_ARGS__) is \\\n")
        init, lvmap = gen_init(fielding, obj_name)
        f.write(trail_slash(indent(init.strip())) + "\n\n")

        # Refresh macro
        f.write(f"\n#define {s.name.upper()}_REFRESH \\\n")
        # [:-1] to remove last semi
        f.write(trail_slash(indent(gen_refresh(fielding, obj_name).strip()[:-1])))
        f.write("\n\n")

        # Setter macro for each field
        for field in s.fields:
            mname = f"{s.name}_set_{field.name}".upper()
            # This double evaluates, but Wacc exprs have no side effects
            # Setting the local and global is probably redundant, but Eh.
            f.write(
                f"#define {mname}(__val) {lvmap[field.name]} = __val; {field.name} = __val\n"
            )


def main():
    for s in [
        Struct(
            "lexer",
            [
                StructField("source", wtype.Array(wtype.Char())),
                StructField("start", wtype.Int()),
                StructField("current", wtype.Int()),
                StructField("lenght", wtype.Int()),
            ],
        ),
        Struct(
            "token",
            [
                StructField("type", wtype.Int()),
                StructField("start", wtype.Int()),
                StructField("length", wtype.Int()),
            ],
        ),
    ]:
        gen_struct(s)

import gen_struct
from wtype import Int, Bool, String, Char, Array


def test_gen_init():
    assert (
        gen_struct.gen_init(gen_struct.StructField("a", Int()), "__obj")
        == "int a = __obj;\n"
    )

    assert (
        gen_struct.gen_init(
            (
                gen_struct.StructField("a", Int()),
                gen_struct.StructField("b", Int()),
            ),
            "__obj",
        )
        == """int __objl = fst __obj;
int __objr = snd __obj;
int a = __objl;
int b = __objr;
"""
    )

    assert (
        gen_struct.gen_init(
            (
                (
                    gen_struct.StructField("a", Int()),
                    (
                        gen_struct.StructField("b", Int()),
                        gen_struct.StructField("c", Bool()),
                    ),
                ),
                (
                    gen_struct.StructField("d", String()),
                    gen_struct.StructField("e", Array(Char())),
                ),
            ),
            "__obj",
        )
        == """pair(int, pair) __objl = fst __obj;
pair(string, char[]) __objr = snd __obj;
int __objll = fst __objl;
pair(int, bool) __objlr = snd __objl;
int a = __objll;
int __objlrl = fst __objlr;
bool __objlrr = snd __objlr;
int b = __objlrl;
bool c = __objlrr;
string __objrl = fst __objr;
char[] __objrr = snd __objr;
string d = __objrl;
char[] e = __objrr;
"""
    )

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
        == """int a = fst __obj;\nint b = snd __obj;\n"""
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
        == """pair(int, pair) __fstobj = fst __obj;
int a = fst __fstobj;
pair(int, bool) __sndfstobj = snd __fstobj;
int b = fst __sndfstobj;
bool c = snd __sndfstobj;
pair(string, char[]) __sndobj = snd __obj;
string d = fst __sndobj;
char[] e = snd __sndobj;
"""
    )

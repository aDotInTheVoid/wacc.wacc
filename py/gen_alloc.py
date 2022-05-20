import pprint
from util import Generate, comment, indent
import itertools

# TODO: Make this in line with new line allocation scheme
# if it turns out we need it.
# https://github.com/aDotInTheVoid/wacc.wacc/issues/7

# pre: sorted(l)
# return pivot, lesseq, greatereq
# kinda funkey because we want the smallest element greater or equal to the pivot
def gen_bsearch(l):
    assert len(l) == len(set(l))
    assert l == sorted(l)
    return _gen_bsearch(l, True)


def _gen_bsearch(l, rightmost):

    if len(l) == 2:
        if rightmost:
            return l[1], _gen_bsearch(l, False), None
        else:
            return l[0], l[0], l[1]
    elif len(l) == 1:
        if rightmost:
            return l[0], l[0], None
        else:
            return l[0]

    mid = len(l) // 2
    pivot = l[mid]
    less = l[: mid + 1]
    greater = l[mid + 1 :]
    return pivot, _gen_bsearch(less, False), _gen_bsearch(greater, rightmost)


def list_of(n):
    match n:
        case int(n):
            return "RETVRN(char[], [" + ",".join("' '" for _ in range(n)) + "])"
        case None:
            return "exit 1"


def gen_calloc_tree(tree):
    match tree:
        case (piv, leq, gt):
            return (
                f"if size <= {piv} then\n"
                + indent(gen_calloc_tree(leq))
                + "\nelse\n"
                + indent(gen_calloc_tree(gt))
                + "\nfi"
            )
        case n:
            return list_of(n)


LENS_NEST = list(
    map(
        list,
        [
            range(10),
            range(10, 100, 10),
            range(100, 1000, 100),
            range(1000, 10000, 1000),
        ],
    )
)

LENS = list(itertools.chain(*LENS_NEST))


def gen_calloc(f):
    f.write("char[] calloc(int size) is\n")
    f.write("")

    f.write(indent(gen_calloc_tree(gen_bsearch(LENS))))

    f.write("\n")
    f.write("end\n")


def gen_alloc():
    with Generate("alloc") as f:
        # TODO: Write comment
        f.write(
            comment("Allocates an array of chars with at least the lenght requested")
            + "\n"
        )
        f.write(
            comment(f"Fails if the requested size is largen than {max(LENS)}") + "\n"
        )
        f.write("\n" + comment("Availible sizes: ") + "\n")
        f.write(comment(pprint.pformat(LENS_NEST)) + "\n")

        gen_calloc(f)


def main():
    gen_alloc()

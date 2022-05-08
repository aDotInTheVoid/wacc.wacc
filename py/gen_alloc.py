from util import Generate, indent
import itertools


# pre: sorted(l)
# return pivot, lesseq, greatereq
# kinda funkey because we want the smallest element greater or equal to the pivot
def gen_bsearch(l, rightmost=True):
    if len(l) == 2:
        if rightmost:
            return l[1], gen_bsearch(l, False), None
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
    return pivot, gen_bsearch(less, False), gen_bsearch(greater, rightmost)


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


def gen_calloc(f):
    f.write("char[] calloc(int size) is\n")
    f.write("")

    tree = list(
        itertools.chain(
            range(10),
            range(10, 100, 10),
            range(100, 1000, 100),
            range(1000, 10000, 1000),
        )
    )

    f.write(indent(gen_calloc_tree(gen_bsearch(tree))))

    f.write("\n")
    f.write("end\n")


def gen_alloc():
    with Generate("alloc") as f:
        gen_calloc(f)


def main():
    gen_alloc()

import heapq

from dataclasses import dataclass, field
from typing import Any


@dataclass(order=True)
class PrioritizedItem:
    priority: int
    item: Any = field(compare=False)


def item_depth(item):
    if isinstance(item, tuple):
        assert len(item) == 2
        return 1 + max(item_depth(item[0]), item_depth(item[1]))
    else:
        return 0


def pairgen(items):
    for i in items:
        assert not isinstance(i, tuple)
    queue = []

    def push(item):
        depth = item_depth(item)
        heapq.heappush(queue, PrioritizedItem(depth, item))

    def pop():
        return heapq.heappop(queue).item

    for i in items:
        push(i)

    while len(queue) > 1:
        l = pop()
        r = pop()
        push((l, r))

    r = pop()
    assert len(queue) == 0
    return r

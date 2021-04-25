from __future__ import annotations


class Node:
    def __init__(self, data: type) -> None:
        self._value: type = data
        self._next: Node = None

    def value(self) -> type:
        return self._value

    def next(self) -> Node:
        return self._next

    def set_next(self, next_node: Node) -> None:
        self._next = next_node


if __name__ == '__main__':
    main()

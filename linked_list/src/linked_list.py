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


class LinkedList:
    def __init__(self) -> None:
        self._head: Node = None
        self._tail: Node = None

    def insert(self, data: type) -> None:
        new_node = Node(data)
        if not self._head:
            self._head = new_node
            self._tail = new_node
            return
        self._tail.set_next(new_node)
        self._tail = self._tail.next()

    def head(self) -> Node:
        return self._head

    def tail(self) -> Node:
        return self._tail


if __name__ == '__main__':
    main()

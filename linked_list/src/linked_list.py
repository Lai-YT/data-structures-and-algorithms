# mypy: --no-strict-optional

from __future__ import annotations
from typing import TypeVar


T = TypeVar('T')

class Node:
    def __init__(self, value: T) -> None:
        self._value: T = value
        self._next: Node = None

    @property
    def value(self) -> T:
        return self._value

    @value.setter
    def value(self, new_value: T) -> None:
        self._value = new_value

    @property
    def next(self) -> Node:
        return self._next

    @next.setter
    def next(self, next_node: Node) -> None:
        self._next = next_node


class LinkedList:
    def __init__(self) -> None:
        self._head: Node = None
        self._tail: Node = None

    def insert(self, data: T) -> None:
        new_node = Node(data)
        if not self._head:
            self._head = new_node
            self._tail = new_node
            return
        self._tail.next = new_node
        self._tail = self._tail.next

    @property
    def head(self) -> Node:
        return self._head

    @property
    def tail(self) -> Node:
        return self._tail

    def is_empty(self) -> bool:
        return self._head is None

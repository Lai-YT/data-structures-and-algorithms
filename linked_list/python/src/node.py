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

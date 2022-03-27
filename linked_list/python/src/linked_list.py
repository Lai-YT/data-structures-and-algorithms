from __future__ import annotations
from typing import Callable, TypeVar


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
    """This is a singly linked list with "head" and "tail" pointers.
    
    Implements the following operations:
        - append(self, data: T) -> None
        - find(self, cond: Callable[[T], bool]) -> Node
    """

    def __init__(self) -> None:
        self._head: Node = None
        self._tail: Node = None

    def append(self, data: T) -> None:
        """Append a new node with "data" as value to the left side of the list."""
        new_node = Node(data)

        if self.is_empty():
            self._head = new_node
            self._tail = new_node
            return
        # the original tail now points to the new node
        self._tail.next = new_node
        # and the new node is now the tail
        self._tail = new_node

    def find(self, cond: Callable[[T], bool]) -> Node:
        """Finds the first node which meets the cond."""
        pass

    @property
    def head(self) -> Node:
        return self._head

    @property
    def tail(self) -> Node:
        return self._tail

    def is_empty(self) -> bool:
        return self._head is None

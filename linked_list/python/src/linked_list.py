from typing import Callable, TypeVar

from src.node import Node


T = TypeVar('T')

class LinkedList:
    """This is a singly linked list with "head" and "tail" pointers.

    Implements the following operations:
        - append(self, data: T) -> None
        - remove(self, cond: Callable[[T], bool]) -> None
        - find(self, cond: Callable[[T], bool]) -> Node
    """

    def __init__(self) -> None:
        self._head: Node = None
        self._tail: Node = None

    def append(self, data: T) -> None:
        """Append a new node with "data" as value to the left side of the list.

        This is an O(1) operation.
        """
        new_node = Node(data)

        if self.is_empty():
            self._head = new_node
            self._tail = new_node
            return
        # the original tail now points to the new node
        self._tail.next = new_node
        # and the new node is now the tail
        self._tail = new_node

    def remove(self, cond: Callable[[T], bool]) -> None:
        """Removes the first node which has value meet the "cond"-ition.

        This is an O(n) operation.
        """
        pre = None
        tar = self._head
        while tar is not None and not cond(tar.value):
            pre = tar
            tar = tar.next

        # node not found
        if pre is self._tail:
            pass
        # remove head
        elif tar is self._head:
            self._head = tar.next
        else:
            pre.next = tar.next

    def find(self, cond: Callable[[T], bool]) -> Node:
        """Finds the first node which has value meet the "cond"-ition.

        This is an O(n) operation.
        """
        node = self._head
        while node is not None and not cond(node.value):
            node = node.next
        return node

    @property
    def head(self) -> Node:
        return self._head

    @property
    def tail(self) -> Node:
        return self._tail

    def is_empty(self) -> bool:
        return self._head is None

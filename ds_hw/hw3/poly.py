from __future__ import annotations
from typing import List

from node import *

# Define the class of the linked list used for polynomial representation
# List class
class Poly_List:
    def __init__(self):
        self.head: Node = None
        self.tail: Node = None
        self.size: int = 0

    # methods for managing the list
    def is_empty(self) -> bool:
        return self.head is None

    def ishead(self, node: Node) -> bool:
        return node == self.head

    def is_tail(self, node: Node) -> bool:
        return node == self.tail

    # get the degree of the polynomial
    @property
    def degree(self) -> int:
        curr = self.head
        degree: int = 0
        # the max algorithm
        while curr is not None:
            if curr.exponent > degree:
                degree = curr.exponent
            curr = curr.next
        return degree

    # insert a term (node) after node p
    def insert_after(self, p: Node, c: float, exp: int) -> None:
        new_node = Node(c, exp)
        curr = self.head
        while curr and curr != p:
            curr = curr.next
        if curr == p:
            new_node.next = curr.next
            curr.next = new_node
        else:
            # cancel insertion if p doesn't exist
            return
        self.size += 1

    # insert a term (node) at head
    def insert_at_head(self, c: float, exp: int) -> None:
        new_node = Node(c, exp)
        if not self.size:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next = self.head
            self.head = new_node

        self.size += 1

    # insert a term (node) at tail
    def insert_at_tail(self, c: float, exp: int) -> None:
        new_node = Node(c, exp)
        if not self.size:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node

        self.size += 1

    # delete a term (node) at head
    def delete_at_head(self) -> None:
        if self.head:
            self.head = self.head.next
            self.size -= 1

    # Method for adding the missing terms and may be used for division
    def padding(self) -> None:
        """
        Assume that the terms will always be in descending order.
        """
        # fill the lost terms between head and tail
        curr = self.head
        while curr and curr.next:
            if curr.exponent - 1 != curr.next.exponent:
                self.insert_after(curr, 0, curr.exponent - 1)
            curr = curr.next

        # fill the lost terms after tail
        while self.tail.exponent != 0:
            self.insert_at_tail(0, self.tail.exponent - 1)

    # This method is used for multiplying the polynomial by a constant m or
    # lifting all terms by a degree d
    def time_const_lift_degree(self, m, d):
        pass

    # This method returns a copy of the polynomial with a new list
    def copy(self) -> Poly_List:
        copy_poly = Poly_List()
        curr = self.head
        while curr:
            copy_poly.insert_at_tail(curr.coefficient, curr.exponent)
            curr = curr.next
        return copy_poly

    # This prints the polynomial in a given format
    def __str__(self) -> str:
        if self.head == None:
            return  ''

        curr = self.head
        str_poly: List[str] = []

        # the head node is special in sign representation
        str_poly.append(f'{curr.coefficient}')
        if curr.exponent > 1:
            str_poly.append(f'x^{curr.exponent}')
        elif curr.exponent == 1:
            str_poly.append('x')
        curr = curr.next

        while curr:
            # coefficient first
            if curr.coefficient == 0:
                curr = curr.next
                continue
            # coefficient 1 is special
            if curr.coefficient > 0 and curr.coefficient != 1:
                str_poly.append(f'+{curr.coefficient}')
            elif curr.coefficient == 1:
                if curr.exponent == 0:
                    str_poly.append('+1')
                    break
                else:
                    str_poly.append('+')
            else:
                str_poly.append(f'{curr.coefficient}')

            # add x and its exponent
            if curr.exponent > 1:
                str_poly.append(f'x^{curr.exponent}')
            elif curr.exponent == 1:
                str_poly.append('x')

            curr = curr.next

        return ''.join(str_poly)

    # this function is kept for teacher's main operation
    def printPolynomial(self) -> None:
        print(self)

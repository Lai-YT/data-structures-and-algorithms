from __future__ import annotations

# Define the class of node in the linked list used for polynomial representation
# Node class
class Node:
    def __init__(self, c: float, exp: int):
        self.coefficient: float = c
        self.exponent: int = exp
        self.next: Node = None

    def set_data(self, c: float, exp: int) -> None:
        self.coefficient = c
        self.exponent = exp

    def __eq__(self, other: Node) -> bool:
        return other is not None \
            and self.coefficient == other.coefficient \
            and self.exponent == other.exponent

    def __ne__(self, other: Node) -> bool:
        return not self.__eq__(other)

    def __add__(self, other: Node) -> Node or None:
        if self.exponent != other.exponent:
            return None
        return Node(self.coefficient + other.coefficient, self.exponent)

    def __sub__(self, other: Node) -> Node or None:
        if self.exponent != other.exponent:
            return None
        return Node(self.coefficient - other.coefficient, self.exponent)

    def __mul__(self, other: Node) -> Node:
        return Node(self.coefficient * other.coefficient,
                    self.exponent + other.exponent)

    def __truediv__(self, other: Node) -> Node:
        return Node(self.coefficient / other.coefficient,
                    self.exponent - other.exponent)

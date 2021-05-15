from typing import List

from node import *
from poly import *

# functions for polynomial operations
"""
Assume that the terms will always be in descending order.
"""

# adding two polynomials
def add(poly1: Poly_List, poly2: Poly_List) -> List[Poly_List]:
    """
    Pick the one with higher degree as the base,
    and than traverse another polynomial to add their coefficient.
    """
    result_poly = Poly_List()
    low_degree_poly = Poly_List()
    # pick high degree
    if poly1.degree >= poly2.degree:
        result_poly = poly1.copy()
        low_degree_poly = poly2
    else:
        result_poly = poly2.copy()
        low_degree_poly = poly1

    result_poly.padding()
    # add their coefficient
    curr_h, curr_l = result_poly.head, low_degree_poly.head
    while curr_l:
        if curr_l.exponent == curr_h.exponent:
            curr_h.set_data(curr_h.coefficient + curr_l.coefficient,
                            curr_h.exponent)
            curr_h, curr_l = curr_h.next, curr_l.next
        else:
            curr_h = curr_h.next
    return [result_poly, None]


# substracting poly2 from poly1
def substract(poly1: Poly_List, poly2: Poly_List) -> List[Poly_List]:
    """
    If minuend has lower degree than subtrahend, fill it up.
    And than traverse the subtrahend to get their coefficient.
    """
    result_poly = poly1.copy()
    result_poly.padding()
    # fill
    while result_poly.degree < poly2.degree:
        result_poly.insert_at_head(0, result_poly.degree + 1)

    # start substraction
    curr_1, curr_2 = result_poly.head, poly2.head
    while curr_2:
        if curr_2.exponent == curr_1.exponent:
            curr_1.set_data(curr_1.coefficient - curr_2.coefficient,
                            curr_1.exponent)
            curr_1, curr_2 = curr_1.next, curr_2.next
        else:
            curr_1 = curr_1.next
    return [result_poly, None]

# multiplying two polynomials
def multiply(poly1: Poly_List, poly2: Poly_List) -> List[Poly_List]:
    curr: Node = poly2.head
    result_poly = Poly_List()
    while curr:
        poly: Poly_List = poly1.copy()
        poly.times_term(curr.coefficient, curr.exponent)
        result_poly = add(result_poly, poly)[0]
        curr = curr.next
    return [result_poly, None]

# dividng poly1 by poly2 and then returning the quotient and remainder
def divide(poly1: Poly_List, poly2: Poly_List) -> List[Poly_List]:
    pass

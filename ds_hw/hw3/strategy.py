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
    # remove leading 0 terms
    curr = result_poly.head
    while curr.coefficient == 0:
        curr = curr.next
        result_poly.delete_at_head()

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
    # remove leading 0 terms
    curr = result_poly.head
    while curr.coefficient == 0:
        curr = curr.next
        result_poly.delete_at_head()

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
    # if poly1 has smaller degree than poly2, poly1 is the remainder, with quotient 0
    if poly2.degree > poly1.degree:
        quotient = Poly_List()
        quotient.insert_at_tail(0, 0)
        return [quotient, poly1]

    # make the polys in standard form: descending and filled
    poly1_remain = poly1.copy()
    poly1_remain.sort()
    poly1_remain.padding()
    poly2.sort()
    poly2.padding()

    quotient = Poly_List()
    while poly1_remain.degree >= poly2.degree:
        sub_poly2 = poly2.copy()
        sub_poly2.times_term(poly1_remain.head.coefficient / poly2.head.coefficient,
                             poly1_remain.degree - poly2.degree)
        quotient.insert_at_tail(poly1_remain.head.coefficient / poly2.head.coefficient,
                                poly1_remain.degree - poly2.degree)
        poly1_remain = substract(poly1_remain, sub_poly2)[0]

    return [quotient, poly1_remain]

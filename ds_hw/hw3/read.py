from typing import Dict, List
import re

from poly import *

# functions for reading and parsing the input file to have the input polynomials and operation

# function for reading lines in the input text file into a list of strings
def read_lines(file_path: str) -> List[str]:
    lines: List[str] = list()
    with open(file_path) as f:
        for line in f:
            lines.append(line.strip('\n'))
    return lines


# function for parsing the line into polynomial with linked list representation
def read_string(s: str) -> Poly_List:
    """
    Split by sign to get each terms,
    and then the second spilt get the coefficient and exponent.
    """

    start: int = 0
    term_list: List[str] = list()
    # first split the by +, - sign to get the terms
    for i, char in enumerate(s):
        if char == '+' or char == '-':
            term_list.append(s[start:i])
            start = i
    # constant term
    term_list.append(s[start:])

    # there will be an empty str at front if the leading term coef is negative
    if not term_list[0]:
        term_list.pop(0)

    poly_from_str = Poly_List()
    for term in term_list:
        # second split for the coef and exp
        # empty element after split represents a 'x',
        # which is important for identify exponent 1 and constant term
        term = re.split('[x^]', term)

        # 3 means there's a coef, x and corresponding exp
        if len(term) == 3:
            coef, _, exp = term
            coef = (float(coef) if coef != '+' else 1)
            poly_from_str.insert_at_tail(coef, int(exp))
        # 2 means exp is 1
        elif len(term) == 2:
            coef, _ = term
            coef = (float(coef) if coef != '+' else 1)
            poly_from_str.insert_at_tail(coef, 1)
        # 1 means constant term
        elif len(term) == 1:
            poly_from_str.insert_at_tail(float(term[0]), 0)

    return poly_from_str

"""
This file contains helpers functions of BST which are not appropriate
to be class methods.
"""


def left_of(i: int) -> int:
    """
    @param
        index of the parent
    @return
        the the index of i's left child, without existence check
    @time
        O(1)
    """
    return i * 2

def right_of(i: int) -> int:
    """
    @param
        index of the parent
    @return
        the the index of i's right child, without existence check
    @time
        O(1)
    """
    return i * 2 + 1

# you may need Python math Module, https://docs.python.org/3/library/math.html
import math
from typing import List

# class of a Binary Search Tree
class BinarySearchTree:
    def __init__(self):
        # index 0 is not used, the root node is now nothing ('X')
        self._base_arr: List[int or str] = [0, 'X']

    # reuqested operation 1
    def insert(self, key: int) -> None:
        """
        @time
            O(n), where n is the size of BST.
            worst case occurs when the BST is unbalanced
        """

        i: int = 1
        while i < len(self._base_arr):  # len needs to be at least i + 1
            if self._base_arr[i] == 'X':
                self._base_arr[i] = key
                break

            # If larger than parent, go right.
            # ('=' included so in-order can be stable)
            elif key >= self._base_arr[i]:
                i = i * 2 + 1
            else:
                i = i * 2
        # list too small
        else:
            # extend to index i (exactly size i + 1), so can add
            self._base_arr.extend(['X' for _ in range(len(self._base_arr), i + 1)])
            self._base_arr[i] = key

    # reuqested operation 2
    def delete(self, key):
        pass

    # reuqested operation 3
    def searchKey(self, key: int) -> str:
        """
        return {key} is found if is found, otherwise NOT found
        @time
            O(n), where n is the size of BST.
            worst case occurs when the BST is unbalanced
        """

        i: int = 1
        while i < len(self._base_arr) and self._base_arr[i] != 'X':
            if self._base_arr[i] == key:
                return f'{key} is found'
            # BST property
            if self._base_arr[i] > key:
                i *= 2
            else:
                i = i * 2 + 1
        return 'NOT found'

    # reuqested operation 4
    def printProperty(self):
        pass

    # reuqested operation 5
    def preorderTraversal(self):
        pass

    # reuqested operation 6
    def postorderTraversal(self):
        pass

    # reuqested operation 7
    def inorderTraversal(self) -> str:
        """
        @time
            O(n), where n is the size of BST.
        """
        # cast to str in-order, filter 'X'
        inorder_list: List[str] = list('')
        # to do iterative traversal, we need a stack to help, which stores the index
        stack: List[int] = list()
        i: int = 1  # start from root
        while True:
            # If something at i, put in the stack and go right.
            if i < len(self._base_arr) and self._base_arr[i] != 'X':
                stack.append(i)
                i *= 2
            # If nothing at i, go back to visit the parent, which means pop,
            # and go down to left.
            elif len(stack):
                i = stack.pop()
                inorder_list.append(str(self._base_arr[i]))
                i = i * 2 + 1
            # both stack and BST are over
            else:
                break

        return ' '.join(inorder_list)


    def __str__(self) -> str:
        """
        link keys with '->'
        @time
            O(N), where N is the size of base array.
        """
        # empty tree
        if self._base_arr[1] == 'X':
            return ''

        string_list: List[str] = list()
        for n in self._base_arr[1:-1]:
            string_list.append(f'{n}->')
        # don't want '->' after the last one
        string_list.append(f'{self._base_arr[-1]}')
        return ''.join(string_list)

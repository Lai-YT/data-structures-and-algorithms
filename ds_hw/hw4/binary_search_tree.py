from typing import List

from bst import *

# This is a wrapper class that wraps a BST,
# which is used to meet the requirements of this homework.

# class of a Binary Search Tree
class BinarySearchTree:
    def __init__(self, bst = BST()):
        self._bst: BST = bst

    @property
    def array(self) -> List[int or str]:
        return self._bst.base_array

    # reuqested operation 1
    def insert(self, key: int) -> None:
        self._bst.insert(key)

    # reuqested operation 2
    def delete(self, key: int) -> None:
        if not self._bst.search(key):
            print(f'key {key} NOT found')
        else:
            self._bst.delete(key)

    # reuqested operation 3
    def searchKey(self, key: int) -> None:
        if not self._bst.search(key):
            print(f'key {key} NOT found')
        else:
            print(f'key {key} is found')

    # reuqested operation 4
    def printProperty(self):
        pass

    # reuqested operation 5
    def preorderTraversal(self) -> None:
        print('Preorder of T : ' + self._bst.preorder())

    # reuqested operation 6
    def postorderTraversal(self) -> None:
        pass

    # reuqested operation 7
    def inorderTraversal(self) -> None:
        print('Inorder of T  : ' + self._bst.inorder())

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
            print(f'key  {key} does not exist')
        else:
            self._bst.delete(key)

    # reuqested operation 3
    def searchKey(self, key: int) -> None:
        if not self._bst.search(key):
            print(f'key  {key} is NOT found')
        else:
            print(f'key {key} is found')

    # reuqested operation 4
    def printProperty(self) -> None:
        height: int = self._bst.height()
        size: int = self._bst.size()
        print(f'The height of T is {height}  and the size of T is {size} .')

    # reuqested operation 5
    def preorderTraversal(self) -> None:
        print('Preorder of T : ', end='')
        preorder_str: str = self._bst.preorder()
        if not preorder_str:
            print('Tree T is empty')
        else:
            print(preorder_str)

    # reuqested operation 6
    def postorderTraversal(self) -> None:
        print('Postorder of T: ', end='')
        postorder_str: str = self._bst.postorder()
        if not postorder_str:
            print('Tree T is empty')
        else:
            print(postorder_str)

    # reuqested operation 7
    def inorderTraversal(self) -> None:
        print('Inorder of T  : ', end='')
        inorder_str: str = self._bst.inorder()
        if not inorder_str:
            print('Tree T is empty')
        else:
            print(inorder_str)

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
        preorder_list: List[int] = self._bst.preorder()
        if not preorder_list:
            print('Tree T is empty')
        else:
            print(' '.join(map(str, preorder_list)))

    # reuqested operation 6
    def postorderTraversal(self) -> None:
        print('Postorder of T: ', end='')
        postorder_list: List[int] = self._bst.postorder()
        if not postorder_list:
            print('Tree T is empty')
        else:
            print(' '.join(map(str, postorder_list)))

    # reuqested operation 7
    def inorderTraversal(self) -> None:
        print('Inorder of T  : ', end='')
        inorder_list: List[int] = self._bst.inorder()
        if not inorder_list:
            print('Tree T is empty')
        else:
            print(' '.join(map(str, inorder_list)))

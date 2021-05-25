from binary_search_tree import *

import unittest


class BinarySearchTreeTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self._bst = BinarySearchTree()

    def test_insert_1(self) -> None:
        self.assertEqual('', str(self._bst))
        self._bst.insert(7)
        self.assertEqual('7', str(self._bst))
        self._bst.insert(7)
        self.assertEqual('7->X->7', str(self._bst))
        self._bst.insert(7)
        self.assertEqual('7->X->7->X->X->X->7', str(self._bst))
        self._bst.insert(1)
        self.assertEqual('7->1->7->X->X->X->7', str(self._bst))
        self._bst.insert(2)
        self.assertEqual('7->1->7->X->2->X->7', str(self._bst))
        self._bst.insert(0)
        self.assertEqual('7->1->7->0->2->X->7', str(self._bst))

    def test_insert_2(self) -> None:
        self._bst.insert(2)
        self._bst.insert(1)
        self._bst.insert(3)
        self._bst.insert(6)
        self._bst.insert(7)
        self._bst.insert(4)
        self._bst.insert(5)
        self.assertEqual('1 2 3 4 5 6 7', self._bst.inorderTraversal())

    def test_inorder_traversal(self) -> None:
        self.assertEqual('', self._bst.inorderTraversal())
        self._bst.insert(7)
        self.assertEqual('7', self._bst.inorderTraversal())
        self._bst.insert(7)
        self.assertEqual('7 7', self._bst.inorderTraversal())
        self._bst.insert(7)
        self.assertEqual('7 7 7', self._bst.inorderTraversal())
        self._bst.insert(1)
        self.assertEqual('1 7 7 7', self._bst.inorderTraversal())
        self._bst.insert(2)
        self.assertEqual('1 2 7 7 7', self._bst.inorderTraversal())
        self._bst.insert(0)
        self.assertEqual('0 1 2 7 7 7', self._bst.inorderTraversal())

    def test_search_key(self) -> None:
        self._bst.insert(2)
        self._bst.insert(1)
        self._bst.insert(3)
        self._bst.insert(6)
        self._bst.insert(7)
        self._bst.insert(4)
        self._bst.insert(5)
        self.assertEqual('1 2 3 4 5 6 7', self._bst.inorderTraversal())

        self.assertEqual('1 is found', self._bst.searchKey(1))
        self.assertEqual('2 is found', self._bst.searchKey(2))
        self.assertEqual('3 is found', self._bst.searchKey(3))
        self.assertEqual('4 is found', self._bst.searchKey(4))
        self.assertEqual('5 is found', self._bst.searchKey(5))
        self.assertEqual('6 is found', self._bst.searchKey(6))
        self.assertEqual('7 is found', self._bst.searchKey(7))

        self.assertEqual('NOT found', self._bst.searchKey(-1))
        self.assertEqual('NOT found', self._bst.searchKey(0))
        self.assertEqual('NOT found', self._bst.searchKey(100))
        self.assertEqual('NOT found', self._bst.searchKey(10000))
        self.assertEqual('NOT found', self._bst.searchKey(-1000))
        self.assertEqual('NOT found', self._bst.searchKey(-0))

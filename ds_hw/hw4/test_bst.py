from bst import *

import unittest


class BinarySearchTreeTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self._bst = BST()

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
        self.assertEqual('1 2 3 4 5 6 7', self._bst.inorder())

    def test_inorder(self) -> None:
        self.assertEqual('', self._bst.inorder())
        self._bst.insert(7)
        self.assertEqual('7', self._bst.inorder())
        self._bst.insert(7)
        self.assertEqual('7 7', self._bst.inorder())
        self._bst.insert(7)
        self.assertEqual('7 7 7', self._bst.inorder())
        self._bst.insert(1)
        self.assertEqual('1 7 7 7', self._bst.inorder())
        self._bst.insert(2)
        self.assertEqual('1 2 7 7 7', self._bst.inorder())
        self._bst.insert(0)
        self.assertEqual('0 1 2 7 7 7', self._bst.inorder())

    def test_search_key(self) -> None:
        self._bst.insert(2)
        self._bst.insert(1)
        self._bst.insert(3)
        self._bst.insert(6)
        self._bst.insert(7)
        self._bst.insert(4)
        self._bst.insert(5)

        self.assertEqual(2, self._bst.search(1))
        self.assertEqual(1, self._bst.search(2))
        self.assertEqual(3, self._bst.search(3))
        self.assertEqual(14, self._bst.search(4))
        self.assertEqual(29, self._bst.search(5))
        self.assertEqual(7, self._bst.search(6))
        self.assertEqual(15, self._bst.search(7))

        self.assertEqual(0, self._bst.search(-1))
        self.assertEqual(0, self._bst.search(0))
        self.assertEqual(0, self._bst.search(100))
        self.assertEqual(0, self._bst.search(10000))
        self.assertEqual(0, self._bst.search(-1000))
        self.assertEqual(0, self._bst.search(-0))

    def test_preorder_1(self) -> None:
        self.assertEqual('', self._bst.preorder())
        self._bst.insert(7)
        self.assertEqual('7', self._bst.preorder())
        self._bst.insert(7)
        self.assertEqual('7 7', self._bst.preorder())
        self._bst.insert(7)
        self.assertEqual('7 7 7', self._bst.preorder())
        self._bst.insert(1)
        self.assertEqual('7 1 7 7', self._bst.preorder())
        self._bst.insert(2)
        self.assertEqual('7 1 2 7 7', self._bst.preorder())
        self._bst.insert(0)
        self.assertEqual('7 1 0 2 7 7', self._bst.preorder())

    def test_preorder_2(self) -> None:
        self._bst.insert(2)
        self._bst.insert(1)
        self._bst.insert(3)
        self._bst.insert(6)
        self._bst.insert(7)
        self._bst.insert(4)
        self._bst.insert(5)
        self.assertEqual('2 1 3 6 4 5 7', self._bst.preorder())

    def test_delete_1(self) -> None:
        self._bst.insert(2)
        self._bst.insert(1)
        self._bst.insert(3)
        self._bst.insert(5)
        self._bst.insert(7)

        self.assertEqual('2->1->3->X->X->X->5->X->X->X->X->X->X->X->7', str(self._bst))
        self._bst.delete(7)
        self.assertEqual('2->1->3->X->X->X->5', str(self._bst))
        self._bst.delete(1)
        self.assertEqual('2->X->3->X->X->X->5', str(self._bst))
        self._bst.delete(3)
        self.assertEqual('2->X->5', str(self._bst))
        self._bst.delete(2)
        self.assertEqual('5', str(self._bst))
        self._bst.delete(5)
        self.assertEqual('', str(self._bst))

    def test_delete_2(self) -> None:
        self._bst.insert(6)
        self._bst.insert(1)
        self._bst.insert(5)
        self._bst.insert(3)
        self._bst.insert(2)
        self._bst.insert(4)

        self._bst.delete(6)
        self.assertEqual('1 2 3 4 5', self._bst.inorder())

    # zig-zag BST
    def test_delete_3(self) -> None:
        self._bst.insert(35)
        self._bst.insert(45)
        self._bst.insert(40)
        self._bst.insert(43)
        self._bst.insert(41)
        self._bst.insert(42)

        self._bst.delete(40)
        self.assertEqual('35 41 42 43 45', self._bst.inorder())

    def test_height_1(self) -> None:
        self.assertEqual(-1, self._bst.height())

        self._bst.insert(2)
        self.assertEqual(0, self._bst.height())

        self._bst.insert(1)
        self.assertEqual(1, self._bst.height())

        self._bst.insert(3)
        self.assertEqual(1, self._bst.height())

        self._bst.insert(5)
        self.assertEqual(2, self._bst.height())

        self._bst.insert(7)
        self.assertEqual(3, self._bst.height())

    def test_height_2(self) -> None:
        self._bst.insert(2)
        self._bst.insert(1)
        self._bst.insert(3)
        self._bst.insert(6)
        self._bst.insert(7)
        self.assertEqual(3, self._bst.height())

        self._bst.insert(4)
        self.assertEqual(3, self._bst.height())

        self._bst.insert(5)
        self.assertEqual(4, self._bst.height())

    # def test_postorder_1(self) -> None:
    #     self.assertEqual('', self._bst.postorder())
    #     self._bst.insert(7)
    #     self.assertEqual('7', self._bst.postorder())
    #     self._bst.insert(7)
    #     self.assertEqual('7 7', self._bst.postorder())
    #     self._bst.insert(7)
    #     self.assertEqual('7 7 7', self._bst.postorder())
    #     self._bst.insert(1)
    #     self.assertEqual('1 7 7 7', self._bst.postorder())
    #     self._bst.insert(2)
    #     self.assertEqual('2 1 7 2 7', self._bst.postorder())
    #     self._bst.insert(0)
    #     self.assertEqual('0 2 1 7 2 7', self._bst.postorder())

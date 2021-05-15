import unittest
from typing import List

from node import *
from poly import *
from strategy import *


class StrategyTestCase(unittest.TestCase):
    def setUp(self):
        self._poly1 = Poly_List()
        self._poly1.insert_at_head(1, 0)
        self._poly1.insert_at_head(1, 1)
        self._poly2 = Poly_List()
        self._poly2.insert_at_head(2, 0)
        self._poly2.insert_at_head(2, 2)

    def test_add(self):
        result1: Poly_List = add(self._poly1, self._poly2)[0]
        self.assertEqual(3, result1.size)
        self.assertEqual(2, result1.degree)
        print(result1)
        self.assertEqual(Node(2, 2), result1.head)
        result1.delete_at_head()
        self.assertEqual(Node(1, 1), result1.head)
        result1.delete_at_head()
        self.assertEqual(Node(3, 0), result1.head)
        # swap addend and augend
        result2: Poly_List = add(self._poly2, self._poly1)[0]
        self.assertEqual(3, result2.size)
        self.assertEqual(2, result2.degree)
        print(result2)
        self.assertEqual(Node(2, 2), result2.head)
        result2.delete_at_head()
        self.assertEqual(Node(1, 1), result2.head)
        result2.delete_at_head()
        self.assertEqual(Node(3, 0), result2.head)

    def test_substract(self):
        result1: Poly_List = substract(self._poly2, self._poly1)[0]
        self.assertEqual(3, result1.size)
        self.assertEqual(2, result1.degree)
        print(result1)
        self.assertEqual(Node(2, 2), result1.head)
        result1.delete_at_head()
        self.assertEqual(Node(-1, 1), result1.head)
        result1.delete_at_head()
        self.assertEqual(Node(1, 0), result1.head)
        # swap
        result2: Poly_List = substract(self._poly1, self._poly2)[0]
        self.assertEqual(3, result2.size)
        self.assertEqual(2, result2.degree)
        print(result2)
        self.assertEqual(Node(-2, 2), result2.head)
        result2.delete_at_head()
        self.assertEqual(Node(1, 1), result2.head)
        result2.delete_at_head()
        self.assertEqual(Node(-1, 0), result2.head)

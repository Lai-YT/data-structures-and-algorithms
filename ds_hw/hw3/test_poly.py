import unittest

from node import *
from poly import *


class PolyTestCase(unittest.TestCase):
    def setUp(self):
        self._poly = Poly_List()

    def test_construct(self):
        self.assertTrue(self._poly.is_empty())
        self.assertIsNone(self._poly.head)
        self.assertIsNone(self._poly.tail)
        self.assertEqual(0, self._poly.size)

    def test_insert_at_head(self):
        self._poly.insert_at_head(2.2, 3)
        self.assertEqual(Node(2.2, 3), self._poly.head)
        self.assertEqual(Node(2.2, 3), self._poly.tail)
        self.assertEqual(1, self._poly.size)

        self._poly.insert_at_head(3.3, 2)
        self.assertEqual(Node(3.3, 2), self._poly.head)
        self.assertEqual(Node(2.2, 3), self._poly.tail)
        self.assertEqual(2, self._poly.size)

        self._poly.insert_at_head(4.1, 1)
        self.assertEqual(Node(4.1, 1), self._poly.head)
        self.assertEqual(Node(2.2, 3), self._poly.tail)
        self.assertEqual(3, self._poly.size)

        self._poly.insert_at_head(5.5, 0)
        self.assertEqual(Node(5.5, 0), self._poly.head)
        self.assertEqual(Node(2.2, 3), self._poly.tail)
        self.assertEqual(4, self._poly.size)

        print(self._poly)

    def test_insert_at_tail(self):
        self._poly.insert_at_tail(5.5, 0)
        self.assertEqual(Node(5.5, 0), self._poly.head)
        self.assertEqual(Node(5.5, 0), self._poly.tail)
        self.assertEqual(1, self._poly.size)

        self._poly.insert_at_tail(4.1, 1)
        self.assertEqual(Node(5.5, 0), self._poly.head)
        self.assertEqual(Node(4.1, 1), self._poly.tail)
        self.assertEqual(2, self._poly.size)

        self._poly.insert_at_tail(3.3, 2)
        self.assertEqual(Node(5.5, 0), self._poly.head)
        self.assertEqual(Node(3.3, 2), self._poly.tail)
        self.assertEqual(3, self._poly.size)

        self._poly.insert_at_tail(2.2, 3)
        self.assertEqual(Node(5.5, 0), self._poly.head)
        self.assertEqual(Node(2.2, 3), self._poly.tail)
        self.assertEqual(4, self._poly.size)

    def test_insert_after(self):
        # 5.5 + 4.1x + 3.3x^2 + 2.2x^3
        self._poly.insert_at_tail(5.5, 0)
        self._poly.insert_at_tail(4.1, 1)
        self._poly.insert_at_tail(3.3, 2)
        self._poly.insert_at_tail(2.2, 3)

        self._poly.insert_after(Node(4.1, 1), 6.1, 4)
        self.assertEqual(5, self._poly.size)
        self.assertEqual(4, self._poly.degree)
        self.assertEqual(Node(5.5, 0), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(4.1, 1), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(6.1, 4), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(3.3, 2), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(2.2, 3), self._poly.head)

    def test_delete_at_head(self):
        # 5.5 + 4.1x + 3.3x^2 + 2.2x^3
        self._poly.insert_at_tail(5.5, 0)
        self._poly.insert_at_tail(4.1, 1)
        self._poly.insert_at_tail(3.3, 2)
        self._poly.insert_at_tail(2.2, 3)

        self._poly.delete_at_head()
        self.assertEqual(Node(4.1, 1), self._poly.head)

        self._poly.delete_at_head()
        self.assertEqual(Node(3.3, 2), self._poly.head)

        self._poly.delete_at_head()
        self.assertEqual(Node(2.2, 3), self._poly.head)

    def test_padding_poly(self):
        self._poly.insert_at_head(5.5, 3)
        self._poly.insert_at_head(4.1, 6)
        self._poly.insert_at_head(3.3, 7)
        self._poly.insert_at_head(2.2, 10)

        self._poly.padding()

        print(self._poly)

        self.assertEqual(11, self._poly.size)
        self.assertEqual(Node(2.2, 10), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(0, 9), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(0, 8), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(3.3, 7), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(4.1, 6), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(0, 5), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(0, 4), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(5.5, 3), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(0, 2), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(0, 1), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(0, 0), self._poly.head)

    def test_copy(self):
        self._poly.insert_at_head(3.3, 7)
        self._poly.insert_at_head(5.5, 3)
        self._poly.insert_at_head(2.2, 10)
        self._poly.insert_at_head(4.1, 6)

        copy_poly = self._poly.copy()
        self.assertEqual(4, copy_poly.size)
        self.assertEqual(10, copy_poly.degree)

        self.assertEqual(Node(4.1, 6), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(2.2, 10), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(5.5, 3), self._poly.head)
        self._poly.delete_at_head()
        self.assertEqual(Node(3.3, 7), self._poly.head)


if __name__ == '__main__':
    unittest.main()

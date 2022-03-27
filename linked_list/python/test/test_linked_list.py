import unittest

from src.linked_list import LinkedList
from src.node import Node


class LinkedListTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self.list = LinkedList()

    def test_init(self) -> None:
        self.assertIsNone(self.list.head)
        self.assertIsNone(self.list.tail)

    def test_first_append(self) -> None:
        self.list.append(25)
        self.assertIsNotNone(self.list.head)
        self.assertIsNotNone(self.list.tail)
        self.assertEqual(25, self.list.head.value)
        self.assertEqual(25, self.list.tail.value)

    def test_multi_append(self) -> None:
        for i in range(100):
            self.list.append(i)
            self.assertEqual(i, self.list.tail.value)

    def test_find(self) -> None:
        for i in range(0, 100, 2):
            # a tuple of (str) i and (int) i, where i is an even number
            self.list.append((str(i), i))

        # should be able to find an even number
        node = self.list.find(lambda x: x[1] == 20)
        self.assertTrue("20", node.value[0])
        self.assertTrue(20, node.value[1])

        # shouldn't find an odd number
        node = self.list.find(lambda x: x[1] == 3)
        self.assertIsNone(node)

    def test_is_empty(self) -> None:
        self.assertTrue(self.list.is_empty())
        self.list.append(0)
        self.assertFalse(self.list.is_empty())


if __name__ == '__main__':
    unittest.main()

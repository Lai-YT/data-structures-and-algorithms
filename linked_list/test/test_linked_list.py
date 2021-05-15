import unittest

import src.linked_list as ll


class NodeTestCase(unittest.TestCase):
    def setUp(self):
        self.node: Node = ll.Node(25)

    def test_value(self):
        self.assertEqual(25, self.node.value())

    def test_next(self):
        self.node.set_next(ll.Node(20))
        next_node: Node = self.node.next()

        self.assertEqual(20, next_node.value())


class LinkedListTestCase(unittest.TestCase):
    def setUp(self):
        self.linked_list = ll.LinkedList()

    def test_init(self):
        self.assertIsNone(self.linked_list.head())
        self.assertIsNone(self.linked_list.tail())

    def test_insert(self):
        # insert one
        self.linked_list.insert(25)
        self.assertIsNotNone(self.linked_list.head())
        self.assertIsNotNone(self.linked_list.tail())
        self.assertEqual(25, self.linked_list.head().value())
        self.assertEqual(25, self.linked_list.tail().value())
        # insert two
        self.linked_list.insert(11)
        self.assertEqual(25, self.linked_list.head().value())
        self.assertEqual(11, self.linked_list.tail().value())

    def test_mult_insert(self):
        for i in range(100):
            self.linked_list.insert(i)
            self.assertEqual(i, self.linked_list.tail().value())

    def test_is_empty(self):
        self.assertTrue(self.linked_list.is_empty())
        self.linked_list.insert(0)
        self.assertFalse(self.linked_list.is_empty())


if __name__ == '__main__':
    unittest.main()

import unittest

import src.linked_list as ll


class LinkedListTestCase(unittest.TestCase):
    def setUp(self):
        self.node: Node = ll.Node(25)

    def test_value(self):
        self.assertEqual(25, self.node.value())

    def test_next(self):
        self.node.set_next(ll.Node(20))
        next_node: Node = self.node.next()

        self.assertEqual(20, next_node.value())


if __name__ == '__main__':
    unittest.main()

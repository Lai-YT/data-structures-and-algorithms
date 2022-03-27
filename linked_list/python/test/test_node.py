import unittest

from src.node import Node


class NodeTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self.node = Node(25)

    def test_value(self) -> None:
        self.assertEqual(25, self.node.value)

    def test_next(self) -> None:
        self.node.next = Node(20)
        next_node = self.node.next

        self.assertEqual(20, next_node.value)


if __name__ == '__main__':
    unittest.main()

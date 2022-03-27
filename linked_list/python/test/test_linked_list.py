import unittest

from src.linked_list import LinkedList, Node


class NodeTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self.node = Node(25)

    def test_value(self) -> None:
        self.assertEqual(25, self.node.value)

    def test_next(self) -> None:
        self.node.next = Node(20)
        next_node = self.node.next

        self.assertEqual(20, next_node.value)


class LinkedListTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self.linked_list = LinkedList()

    def test_init(self) -> None:
        self.assertIsNone(self.linked_list.head)
        self.assertIsNone(self.linked_list.tail)

    def test_append(self) -> None:
        # append one
        self.linked_list.append(25)
        self.assertIsNotNone(self.linked_list.head)
        self.assertIsNotNone(self.linked_list.tail)
        self.assertEqual(25, self.linked_list.head.value)
        self.assertEqual(25, self.linked_list.tail.value)
        # append two
        self.linked_list.append(11)
        self.assertEqual(25, self.linked_list.head.value)
        self.assertEqual(11, self.linked_list.tail.value)

    def test_multi_append(self) -> None:
        for i in range(100):
            self.linked_list.append(i)
            self.assertEqual(i, self.linked_list.tail.value)

    def test_find(self) -> None:
        for i in range(0, 100, 2):
            # a tuple of (str) i and (int) i, where i is an even number
            self.linked_list.append((str(i), i))

        # should be able to find an even number
        node = self.linked_list.find(lambda x: x[1] == 20)
        self.assertTrue("20", node.value[0])
        self.assertTrue(20, node.value[1])

        # shouldn't find an odd number
        node = self.linked_list.find(lambda x: x[1] == 3)
        self.assertIsNone(node)

    def test_is_empty(self) -> None:
        self.assertTrue(self.linked_list.is_empty())
        self.linked_list.append(0)
        self.assertFalse(self.linked_list.is_empty())


if __name__ == '__main__':
    unittest.main()

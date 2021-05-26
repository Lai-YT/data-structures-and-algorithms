from binary_search_tree import *


# initializing a BST
def test_1(tree: BinarySearchTree) -> None:
    print(T.array)
    # T.printProperty()
    T.preorderTraversal()
    # T.postorderTraversal()
    T.inorderTraversal()


def test_2(tree: BinarySearchTree) -> None:
    print(T.searchKey(9))
    T.insert(35)
    print(T.array)
    # T.printProperty()
    T.preorderTraversal()
    # T.postorderTraversal()
    T.inorderTraversal()

# Simple test on insertions
def test_3(tree: BinarySearchTree) -> None:
    T.insert(45)
    T.insert(40)
    T.insert(43)
    T.insert(41)
    T.insert(42)
    print(T.array)
    # T.printProperty()
    T.preorderTraversal()
    # T.postorderTraversal()
    T.inorderTraversal()

# Simple test on deletions
def test_4(tree: BinarySearchTree) -> None:
    T.delete(30)
    T.delete(38)
    T.delete(40)
    print(T.array)
    # T.printProperty()
    T.preorderTraversal()
    # T.postorderTraversal()
    T.inorderTraversal()


if __name__ == '__main__':
    T = BinarySearchTree()
    test_1(T)
    test_2(T)
    test_3(T)
    test_4(T)

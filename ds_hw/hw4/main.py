from binary_search_tree import *

# tests from the homework

# initializing a BST
def test_1(tree: BinarySearchTree) -> None:
    print(T.array)
    T.printProperty()
    T.preorderTraversal()
    T.postorderTraversal()
    T.inorderTraversal()


def test_2(tree: BinarySearchTree) -> None:
    print(T.searchKey(9))
    T.insert(35)
    print(T.array)
    T.printProperty()
    T.preorderTraversal()
    T.postorderTraversal()
    T.inorderTraversal()

# Simple test on insertions
def test_3(tree: BinarySearchTree) -> None:
    T.insert(45)
    T.insert(40)
    T.insert(43)
    T.insert(41)
    T.insert(42)
    print(T.array)
    T.printProperty()
    T.preorderTraversal()
    T.postorderTraversal()
    T.inorderTraversal()

# Simple test on deletions
def test_4(tree: BinarySearchTree) -> None:
    T.delete(30)
    T.delete(38)
    T.delete(40)
    print(T.array)
    T.printProperty()
    T.preorderTraversal()
    T.postorderTraversal()
    T.inorderTraversal()


if __name__ == '__main__':
    T = BinarySearchTree()
    test_1(T)
    print()

    test_2(T)
    print()

    test_3(T)
    print()

    test_4(T)
    print()

    # [0, 'X']
    # The height of T is -1  and the size of T is 0 .
    # Preorder of T : Tree T is empty
    # Postorder of T: Tree T is empty
    # Inorder of T  : Tree T is empty

    # key  9 is NOT found
    # None
    # [0, 35]
    # The height of T is 0  and the size of T is 1 .
    # Preorder of T : 35
    # Postorder of T: 35
    # Inorder of T  : 35

    # [0, 35, 'X', 45, 'X', 'X', 40, 'X', 'X', 'X', 'X', 'X', 'X', 43, 'X', 'X',
    # 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 41, 'X', 'X', 'X', 'X',
    # 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',
    # 'X', 'X', 'X', 'X', 'X', 'X', 'X', 42]
    # The height of T is 5  and the size of T is 6 .
    # Preorder of T : 35 45 40 43 41 42
    # Postorder of T: 42 41 43 40 45 35
    # Inorder of T  : 35 40 41 42 43 45

    # key  30 does not exist
    # key  38 does not exist
    # [0, 35, 'X', 45, 'X', 'X', 41, 'X', 'X', 'X', 'X', 'X', 'X', 43, 'X', 'X',
    # 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 42]
    # The height of T is 4  and the size of T is 5 .
    # Preorder of T : 35 45 41 43 42
    # Postorder of T: 42 43 41 45 35
    # Inorder of T  : 35 41 42 43 45

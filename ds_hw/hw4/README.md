# Programming (Binary Search Trees)
In this problem, you need to implement an ***array-based binary search tree*** ***T*** with the following associated operations(methods) using Python. We assume that each node is represented by a key value which is an integer. The operations include:
1. `insert(x)`: insert a node with key ***x*** into ***T***.
2. `delete(x)`: delete a node with key ***x*** from ***T***.
3. `searchKey(x)`: perform the search process from the root; if the search fails, print `NOT found`; otherwise, print `x is found`.
4. `printProperty()`: print out the properties of tree ***T***, including the height and size of ***T***.
5. `preorderTraversal()`: list all the nodes using a preorder traversal.
6. `postorderTraversal()`: list all the nodes using a postorder traversal.
7. `inorderTraversal()`: list all the nodes using a inorder traversal.

The binary search tree will be built or defined as a class, `BinarySearchTree`, and the operations mentioned above are defined as the methods. Of course, you can have other auxiliary methods. Initially, the binary search tree is empty. Your program allows the user to search, insert, and delete a node with a key. Please run `preorderTraversal()`, `postorderTraversal()`, and `inorderTraversal()` for the same binary search tree to see what you can observe.

[Python math Module](https://docs.python.org/3/library/math.html)

## Classes

### BST

This is a more general binary search tree, but not exactly what this homework wants.

### BinarySearchTree

This is a wrapper class that has all the methods above. \
*BinarySearchTree* wraps a *BST* and delegates all the works by calling corresponding methods.

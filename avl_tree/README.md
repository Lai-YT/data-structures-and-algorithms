# AVL tree

AVL tree is a highly balanced binary search tree. It's height *h* is less than *1.44lgn*, where *n* is the number of elements.

## Complexity

|Operation       |Average    |Worst case|
|----------------|-----------|----------|
|Space           |O(*n*)     |O(*n*)    |
|Find            |O(*lg(n)*) |O(*lg(n)* |
|Insert (Update) |O(*lg(n)*) |O(*lg(n)* |
|Delete          |O(*lg(n)*) |O(*lg(n)* |

When inserting, the original `TreeNode` data will be updated if key duplicates, i.e., no duplicate keys in the tree.

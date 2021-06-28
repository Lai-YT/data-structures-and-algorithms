# AVL tree

AVL tree is a highly balanced binary search tree. \
It's height *h* is less than *1.44lgn*, where *n* is the number of elements.

Supported operations and corresponding time complexities:
- Search   - O(lgn)
- Insert   - O(lgn) (can do implicit data update)
- Delete   - O(lgn)
- Traverse - O(n)
- Height   - O(1)

When inserting, the original TreeNode data will be updated if key duplicates. \
So no duplicate keys in the tree.

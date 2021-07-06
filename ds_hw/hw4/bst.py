from math import floor, log2
from typing import List, Union

from bst_helper import left_of, right_of


class BST:
    """This is an array-based(Python List) Binary Search Tree(BST).
    @operation(param type) -- return type,    worst case time complexity
        insert(key: int)   -- None,           O(2^h)
        delete(key: int)   -- None,           O(2^h)
        search(key: int)   -- index: int,     O(h)
        height()           -- int,            O(1)
        size()             -- int,            O(1)
        empty()            -- bool,           O(1)
        preorder()         -- List[key: int], O(n)
        postorder()        -- List[key: int], O(n)
        inorder()          -- List[key: int], O(n)
    Where n is the size and h is the height of BST.
    """

    def __init__(self):
        # index 0 is not used, the root node is now nothing ('X')
        self._base_arr: List[Union[int, str]] = [0, 'X']

    def _node_exist(self, i: int) -> bool:
        """
        This is a helper method that checks if there's a node at index i.
        @return
            True if yes.
        @time
            O(1)
        """
        return i < len(self._base_arr) and self._base_arr[i] != 'X'

    @property
    def base_array(self) -> List[Union[int, str]]:
        return self._base_arr

    def insert(self, key: int) -> None:
        """
        @time
            O(2^h), where h is the height of BST.
            This is the time we need to extend a whole new level of 'X'.

            O(h), except the extension, we have an order of h.
        """

        i: int = 1
        while i < len(self._base_arr):  # len needs to be at least i + 1
            # found the place to insert
            if self._base_arr[i] == 'X':
                self._base_arr[i] = key
                return

            # If larger than parent, go right.
            # ('=' included so in-order can be stable)
            elif key >= self._base_arr[i]:
                i = right_of(i)
            else:
                i = left_of(i)
        # list too small
        else:
            # extend to index i (exactly size i + 1), so can insert
            self._base_arr.extend(['X'] * (i + 1 - len(self._base_arr)))
            self._base_arr[i] = key

    # Directly pass the index i if you know where the key is.
    # KW parameter is used to give us a flavor when recursive call.
    def delete(self, key: int = None, *, i: int = 0) -> None:
        """
        @technique
            Case 1:
            Replace by the right-most node of the left sub-tree as the first choice,
            left-most of the right sub-tree if only right sub-tree exist.
            Case 2:
            If neither left nor right sub-tree exist, we're down at the leaf,
            deletion is straightforward.

            We do Case 1 recursively until we reach Case 2, which is the base case.

        @time
            O(2^h), where h is the height of BST.
            This is the time we need to remove trailing 'X's.

            O(h), except the removal, we have an order of h.
        """
        # step 1: find the target node to delete
        if not i:
            i = self.search(key)
        # no such node
        if not i:
            return
        # step 2-1: if the left sub-tree exist, get the rightmost one in it to replace with
        elif self._node_exist(left_of(i)):
            # down to left sub-tree
            replace: int = left_of(i)
            # start looking for the rightmost one
            while self._node_exist(right_of(replace)):
                replace = right_of(replace)
            # replacement
            self._base_arr[i] = self._base_arr[replace]
            # we have to call delete recursively because we delete this very 'replace' node
            self.delete(i=replace)
        # step 2-2: if the right sub-tree exist, get the leftmost one in it to replace with
        elif self._node_exist(right_of(i)):
            # down to right sub-tree
            replace: int = right_of(i)
            # start looking for the leftmost one
            while self._node_exist(left_of(replace)):
                replace = left_of(replace)
            # replacement
            self._base_arr[i] = self._base_arr[replace]
            # we have to call delete recursively because we delete this very 'replace' node
            self.delete(i=replace)
        # last step: target is leaf, just delete it and so finish the deletion
        else:
            self._base_arr[i] = 'X'
            # Remove trailing 'X's, so keep the length of base array as short as possible.
            while len(self._base_arr) > 2 and self._base_arr[-1] == 'X':
                self._base_arr.pop()

    def search(self, key: int) -> int:
        """
        @return
            The smallest index of key if key exist,
            otherwise 0.
        @time
            O(h), where h is the height of BST.
        """

        i: int = 1
        while self._node_exist(i):
            if self._base_arr[i] == key:
                return i
            # BST property
            if self._base_arr[i] > key:
                i = left_of(i)
            else:
                i = right_of(i)
        return 0

    # Use as a helper method in many other methods.
    def empty(self) -> bool:
        """
        @return
            Whether the BST is empty or not.
        @time
            O(1)
        """
        return self._base_arr[1] =='X'

    def height(self) -> int:
        """
        @time
            O(1)
        """
        # Since the length of base array is always as short as possible,
        # we can calculate the height of BST as floor of lg(N),
        # where N is the length of base array (index 0 is not counted).
        if self.empty():
            return -1
        return floor(log2(len(self._base_arr) - 1))

    def size(self) -> int:
        """
        @return
            How many keys(nodes) there are in the BST.
        @time
            O(n), where n is the size of BST,
            since we take a traversal.
        """
        # number of nodes in the pre-order list
        return len(self.preorder())

    def preorder(self) -> List[int]:
        """
        @return
            List of keys in pre-order traversal.
        @time
            O(n), where n is the size of BST.
        """

        preorder_list: List[int] = list()
        # to do iterative traversal, we need a stack to help, which stores the index
        stack: List[int] = [1]  # start from root
        # If the stack is empty, the traversal is over.
        while len(stack):
            i: int = stack.pop()
            # visit if something at i
            if self._node_exist(i):
                preorder_list.append(self._base_arr[i])
                # to let left be visited before right, append right first(stack is LIFO)
                stack.append(right_of(i))
                stack.append(left_of(i))
            # else: pass
                # skip if nothing at i

        return preorder_list

    def postorder(self) -> List[int]:
        """
        @return
            List of keys in post-order traversal.
        @time
            O(n), where n is the size of BST.
        """

        postorder_list: List[int] = list()

        def _recur_post(i: int) -> None:
            """
            This is an inner helper method used by postorder(),
            it recursively calls itself to append keys in post-order.
            """

            if self._node_exist(left_of(i)):
                _recur_post(left_of(i))
            if self._node_exist(right_of(i)):
                _recur_post(right_of(i))
            postorder_list.append(self._base_arr[i])
        # end _recur_post

        if not self.empty():
            _recur_post(1)
        return postorder_list

    def inorder(self) -> List[int]:
        """
        @return
            List of keys in in-order traversal.
        @time
            O(n), where n is the size of BST.
        """

        inorder_list: List[int] = list()
        # to do iterative traversal, we need a stack to help, which stores the index
        stack: List[int] = list()
        i: int = 1  # start from root
        while True:
            if self._node_exist(i):
                stack.append(i)
                i = left_of(i)
            elif len(stack):
                i = stack.pop()
                inorder_list.append(self._base_arr[i])
                i = right_of(i)
            # both stack and BST are over
            else:
                break

        return inorder_list

    def __str__(self) -> str:
        """
        link keys with '->'
        @time
            O(2^n), where n is the size of BST.
        """

        if self.empty():
            return ''

        string_list: List[str] = list()
        for n in self._base_arr[1:-1]:
            string_list.append(f'{n}->')
        # don't want '->' after the last one
        string_list.append(f'{self._base_arr[-1]}')
        return ''.join(string_list)

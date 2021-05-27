from math import floor, log2
from typing import List


class BST:
    def __init__(self):
        # index 0 is not used, the root node is now nothing ('X')
        self._base_arr: List[int or str] = [0, 'X']

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
    def base_array(self) -> List[int or str]:
        return self._base_arr

    def insert(self, key: int) -> None:
        """
        @time
            O(h), where h is the height of BST.
        """

        i: int = 1
        while i < len(self._base_arr):  # len needs to be at least i + 1
            if self._base_arr[i] == 'X':
                self._base_arr[i] = key
                break

            # If larger than parent, go right.
            # ('=' included so in-order can be stable)
            elif key >= self._base_arr[i]:
                i = i * 2 + 1
            else:
                i = i * 2
        # list too small
        else:
            # extend to index i (exactly size i + 1), so can add
            self._base_arr.extend(['X' for _ in range(len(self._base_arr), i + 1)])
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
            O(N), where N is the size of base array.
            Worst case occurs when all 'X' except root after deletion.

            O(h), except the removal of 'X's we have a order of h,
            where h is the height of BST.
        """
        # step 1: find the target node to delete
        if not i:
            i = self.search(key)
        # no such node
        if not i:
            return
        # step 2-1: if the left sub-tree exist, get the rightmost one in it to replace with
        elif self._node_exist(i * 2):
            # down to left sub-tree
            replace: int = i * 2
            # start looking for the rightmost one
            while self._node_exist(replace * 2 + 1):
                replace = replace * 2 + 1
            # replacement
            self._base_arr[i] = self._base_arr[replace]
            # we have to call delete recursively because we delete this very 'replace' node
            self.delete(i=replace)
        # step 2-2: if the right sub-tree exist, get the leftmost one in it to replace with
        elif self._node_exist(i * 2 + 1):
            # down to right sub-tree
            replace: int = i * 2 + 1
            # start looking for the leftmost one
            while self._node_exist(replace * 2):
                replace = replace * 2
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
                i *= 2
            else:
                i = i * 2 + 1
        return 0

    def height(self) -> int:
        """
        @time
            O(1)
        """
        # Since the length base array is always as short as possible,
        # we can calculate the heigh of BST as floor of lg(N),
        # where N is the length of base array (index 0 is not counted).
        if self._base_arr[1] == 'X':
            return -1
        return floor(log2(len(self._base_arr) - 1))

    def preorder(self):
        """
        @time
            O(n), where n is the size of BST.
        """
        # cast to str pre-order, filter 'X'
        preorder_list: List[str] = list('')
        # to do iterative traversal, we need a stack to help, which stores the index
        stack: List[int] = [1]  # start from root
        # If the stack is empty, the traversal is over.
        while len(stack):
            i: int = stack.pop()
            # visit if something at i
            if self._node_exist(i):
                preorder_list.append(str(self._base_arr[i]))
                # to let left be visited before right, append right first(stack is LIFO)
                stack.append(i * 2 + 1)
                stack.append(i * 2)
            # else: pass
                # skip if nothing at i

        return ' '.join(preorder_list)

    def postorder(self):
        pass

    def inorder(self) -> str:
        """
        @time
            O(n), where n is the size of BST.
        """
        # cast to str in-order, filter 'X'
        inorder_list: List[str] = list('')
        # to do iterative traversal, we need a stack to help, which stores the index
        stack: List[int] = list()
        i: int = 1  # start from root
        while True:
            # If something at i, put in the stack and go right.
            if self._node_exist(i):
                stack.append(i)
                i *= 2
            # If nothing at i, go back to visit the parent, which means pop,
            # and go down to left.
            elif len(stack):
                i = stack.pop()
                inorder_list.append(str(self._base_arr[i]))
                i = i * 2 + 1
            # both stack and BST are over
            else:
                break

        return ' '.join(inorder_list)

    def __str__(self) -> str:
        """
        link keys with '->'
        @time
            O(N), where N is the length of base array.
        """
        # empty tree
        if self._base_arr[1] == 'X':
            return ''

        string_list: List[str] = list()
        for n in self._base_arr[1:-1]:
            string_list.append(f'{n}->')
        # don't want '->' after the last one
        string_list.append(f'{self._base_arr[-1]}')
        return ''.join(string_list)

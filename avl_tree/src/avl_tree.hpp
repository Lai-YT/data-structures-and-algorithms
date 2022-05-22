#ifndef SRC_AVL_TREE_HPP_
#define SRC_AVL_TREE_HPP_

#ifndef ASSERT_DEBUG
  #define ASSERT_DEBUG  /* enable assertion macros */
#endif

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

#include "debug.hpp"
#include "tree_node.hpp"


template<typename DataType, typename KeyType>
class AVLTree {
  using Node = TreeNode<DataType, KeyType>;

public:
  // const qualifier is to prevent link-breaking from the outside.
  // Can't Search and modify the data from the outside.
  // Use Search(if found) + Insert(new_data, corresponding_key) to update data.
  const Node* Search(const KeyType& key) const {
    Node* cur = root_;
    while (cur && key != cur->key) {
      cur = key < cur->key ? cur->left : cur->right;
    }
    return cur;
  }

  // In-order traversal. In ascending order with respect to keys.
  std::vector<DataType> Traverse() const {
    std::vector<DataType> res;
    RecursiveTraverse_(root_, res);
    return std::move(res);
  }

  /** Insert the `key`-`value` pair into tree; if the key already exist, value is updated. */
  void Insert(const DataType& data, const KeyType& key) {
    root_ = RecursiveInsert_(root_, new Node(data, key));
  }

  /** Deletes the node with `key` from the tree; no changes if the `key` doesn't exist */
  void Delete(const KeyType& key) {
    root_ = RecursiveDelete_(root_, key);
  }

  int Height() const {
    return Height_(root_);
  }

  AVLTree() = default;

  // Post-order to delete children before parent.
  ~AVLTree() {
    if (root_) {
      std::stack<Node*> s;
      s.push(root_);
      while (!s.empty()) {
        Node* cur = s.top();
        // Push parent and it's right & left child in s. (delete order: left->right->parent)
        // Mark parent's right & right null. So the time we see a Node with no child,
        // we know it's children were already deleted and we can delete this Node, too.
        if (!cur->left && !cur->right) {
          s.pop();
          delete cur;
        }
        if (cur->right) {
          s.push(cur->right);
          cur->right = nullptr;
        }
        if (cur->left) {
          s.push(cur->left);
          cur->left = nullptr;
        }
      }
    }
  }

private:
  int Height_(const Node* const node) const {
    return node ? node->height : -1;
  }

  // height left - right
  int BalanceFactor_(const Node* const node) const {
    return node ? Height_(node->left) - Height_(node->right) : 0;
  }

  void UpdateHeight_(Node* const node) {
    ASSERT(node);
    node->height = std::max(Height_(node->left), Height_(node->right)) + 1;
  }

  /** The desired `Insert` method has no return value, hidden by this helper method. */
  Node* RecursiveInsert_(Node* const node, Node* const new_node) {
    /* reach the leaf, insert */
    if (!node) {
      return new_node;
    }

    /* duplicate, implicit update */
    if (new_node->key == node->key) {
      node->data = new_node->data;
      delete new_node;
      return node;  /* structure not change, balanced */
    }

    if (new_node->key < node->key) {
      node->left = RecursiveInsert_(node->left, new_node);
    } else {
      node->right = RecursiveInsert_(node->right, new_node);
    }

    /* subtree structure has changed, re-balance */
    UpdateHeight_(node);
    return MakeBalance_(node);
  }

  /**
   * The desired `Delete` method has no return value, hidden by this helper method.
   *
   * When the target node is found, there are 4 conditions:
   *  (1) it's a left
   *  (2) has only right child
   *  (3) has only left child
   *  (4) has child on both side
   */
  Node* RecursiveDelete_(Node* node, const KeyType key) {
    /* key not exist */
    if (!node) {
      return nullptr;
    }

    if (key < node->key) {
      node->left = RecursiveDelete_(node->left, key);
    } else if (key > node->key) {
      node->right = RecursiveDelete_(node->right, key);
    } else {
      /* (1) is leaf */
      if (Height_(node) == 0) {
        delete node;
        return nullptr;
      }
      /* (2) only right, link it up */
      if (!node->left) {
        Node* temp = node->right;
        delete node;
        return temp;
      }
      /* (3) only left, link it up */
      if (!node->right) {
        Node* temp = node->left;
        delete node;
        return temp;
      }
      /* (4) Complete node. Delete `node` by replacing it with the node which
        has the biggest key in the left subtree and turn to delete that node
        since it's now duplicated.
        NOTE: may also replace `node` with the smallest node from right subtree.
      */
      Node* predecessor = GetNodeWithMaxKey_(node->left);
      node->data = predecessor->data;
      node->key = predecessor->key;
      node->left = RecursiveDelete_(node->left, predecessor->key);
    }

    UpdateHeight_(node);
    return MakeBalance_(node);
  }

  /** Returns the right-most node in the right subtree. */
  Node* GetNodeWithMaxKey_(Node* root) const {
    while (root->right) {
      root = root->right;
    }
    return root;
  }

  void RecursiveTraverse_(const Node* const node, std::vector<DataType>& res) const {
    if (!node) {
      return;
    }
    RecursiveTraverse_(node->left, res);
    res.push_back(node->data);
    RecursiveTraverse_(node->right, res);
  }

  /**
   * Makes the tree rooted by `node` baclanced and returns the new root.
   * There are 5 conditions:
   *  (1) left-left heavy
   *  (2) left-right heavy
   *  (3) right-right heavy
   *  (4) right-left heavy
   *  (5) balanced
   */
  Node* MakeBalance_(Node* const node) {
    /* left heavy */
    if (BalanceFactor_(node) > 1) {
      /* (1) left-left heavy */
      if (node->left->left) {
        return RightRotate_(node);
      }
      /* (2) left-right heavy: left child rotate left + `node` rotate right */
      node->left = LeftRotate_(node->left);
      return RightRotate_(node);
    }

    /* right heavy */
    if (BalanceFactor_(node) < -1) {
      /* (3) right-right heavy */
      if (node->right->right) {
        return LeftRotate_(node);
      }
      /* (4) right-left heavy: right child rotate right + `node` rotate left */
      node->right = RightRotate_(node->right);
      return LeftRotate_(node);
    }

    /* (5) already (still) balanced */
    return node;
  }

  /** Rotates `node` to the left and returns the new root. */
  Node* LeftRotate_(Node* const node) {
    Node* right_node = node->right;
    Node* right_left_node = right_node->left;
    /* Moves the right-left node to the right,
      and then `node` to the left of the right node. */
    node->right = right_left_node;
    right_node->left = node;

    /* `node` is now under the original right node, so update `node` first. */
    UpdateHeight_(node);
    UpdateHeight_(right_node);

    return right_node;
  }

  /** Rotates `node` to the right and returns the new root. */
  Node* RightRotate_(Node* const node) {
    Node* left_node = node->left;
    Node* left_right_node = left_node->right;

    /* Moves the left-right node to the left,
      and then `node` to the right of the left node. */
    node->left = left_right_node;
    left_node->right = node;

    /* `node` is now under the orignal left node, so update `node` first. */
    UpdateHeight_(node);
    UpdateHeight_(left_node);

    return left_node;
  }


  Node* root_ = nullptr;
};


#endif /* end of include guard: SRC_AVL_TREE_HPP_ */


// Resources
//  traversals: https://shubo.io/iterative-binary-tree-traversal/

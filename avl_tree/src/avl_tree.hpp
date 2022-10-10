#ifndef SRC_AVL_TREE_HPP_
#define SRC_AVL_TREE_HPP_

#ifndef ASSERT_DEBUG
  #define ASSERT_DEBUG  /* enable assertion macros */
#endif

#include <algorithm>
#include <cmath>
#include <optional>
#include <stack>
#include <utility>  /* move */
#include <vector>

#include "debug.hpp"
#include "tree_node.hpp"

/*
* @brief AVL tree is a self-balancing binary search tree (BST).
*
* Implements the following operations:
*  - std::optional<V> Search(const K& key) const
*  - void Insert(const KeyValuePair<K, V>& key_value_pair)
*  - void Delete(const K& key)
*/
template<typename K, typename V>
class AVLTree {
  using Node = TreeNode<K, V>;

public:
  /**
   * @brief Returns an optional object, contains the value of the node with `key` if found.
   *
   * Modifying the returned value does not affect the tree.
   *
   * @complex O(lg(n)): the height of the tree.
   */
  std::optional<V> Search(const K& key) const {
    const Node* cur = root_;
    while (cur && key != cur->key()) {
      cur = key < cur->key() ? cur->left() : cur->right();
    }
    return cur ? std::optional(cur->value()) : std::optional<V>();
  }

  /** In-order traversal. In ascending order with respect to keys. */
  std::vector<V> Traverse() const {
    std::vector<V> res{};
    res.reserve(exp2(this->height()) /* approx. */);

    /* Down to the left-most node first and then pop bottom-up;
      once a left child is visited, go up a level and visit the parent,
      then go to the right subtree and again down to its left-most node.
      Recursively. */
    std::stack<Node*> s{};
    Node* cur = root_;
    while (cur || !s.empty()) {
      if (cur) {
        s.push(cur);
        cur = cur->left();
      } else {
        Node* node = s.top();
        s.pop();
        res.push_back(node->value());
        cur = node->right();
      }
    }
    return std::move(res);  /* avoid expensive copy */
  }

  /**
   * @brief Insert the `key`-`value` pair into tree; if the key already exist,
   * value is updated.
   * @complex O(lg(n))
   */
  void Insert(const KeyValuePair<K, V>& p) {
    root_ = RecursiveInsert_(root_, new Node(p));
  }

  /**
   * @brief Deletes the node with `key` from the tree; no changes if the `key`
   * doesn't exist.
   * @complex O(lg(n))
   */
  void Delete(const K& key) {
    root_ = RecursiveDelete_(root_, key);
  }

  /** @complex O(1) */
  int height() const {
    return GetHeight_(root_);
  }

  AVLTree() = default;

  /** Traverse in post-order to delete children before parent. */
  ~AVLTree() {
    if (!root_) {
      return;
    }
    /* refer to
      https://shubo.io/iterative-binary-tree-traversal/
      for traversals */
    std::stack<Node*> s{};
    s.push(root_);
    while (!s.empty()) {
      Node* cur = s.top();
      /* Push parent and it's right & left child in s.
        (delete order: left -> right -> parent)
        Mark parent's right & right as null so at the time we see a node with no
        child, we know it's children were already deleted and we can delete
        this node, too. */
      if (!cur->left() && !cur->right()) {
        s.pop();
        delete cur;
        cur = nullptr;
        continue;
      }
      ASSERT(cur);
      if (cur->right()) {
        s.push(cur->right());
        cur->set_right(nullptr);
      }
      if (cur->left()) {
        s.push(cur->left());
        cur->set_left(nullptr);
      }
    }
  }

private:
  Node* root_ = nullptr;

  /** safe under null pointer */
  int GetHeight_(const Node* const node) const {
    return node ? node->height() : -1;
  }

  /** height left - right */
  int BalanceFactor_(const Node* const node) const {
    return node ? GetHeight_(node->left()) - GetHeight_(node->right()) : 0;
  }

  /**
   * Make sure you call this method on the nodes affected by insertion/deletion
   * to maintain the height of nodes correctly.
   */
  void UpdateHeight_(Node* const node) const {
    ASSERT(node);
    node->set_height(
        std::max(GetHeight_(node->left()), GetHeight_(node->right())) + 1
    );
  }

  /**
   * @brief The desired `Insert` method has no return value, hidden by this helper method.
   * @complex O(lg(n)): bottom up on the insertion path, at most the height.
   */
  Node* RecursiveInsert_(Node* const node, Node* const new_node) {
    /* reach the leaf, insert */
    if (!node) {
      return new_node;
    }

    /* duplicate, implicit update */
    if (new_node->key() == node->key()) {
      node->set_value(new_node->value());
      delete new_node;
      return node;  /* structure not change, balanced */
    }

    if (new_node->key() < node->key()) {
      node->set_left(RecursiveInsert_(node->left(), new_node));
    } else {
      node->set_right(RecursiveInsert_(node->right(), new_node));
    }

    /* subtree structure has changed, re-balance */
    UpdateHeight_(node);
    return MakeBalance_(node);
  }

  /**
   * @brief The desired `Delete` method has no return value, hidden by this
   * helper method.
   *
   * When the target node is found, there are 4 conditions:
   *  (1) it's a left
   *  (2) has only right child
   *  (3) has only left child
   *  (4) has child on both side
   *
   * @complex O(lg(n)): bottom up on the insertion path, at most the height.
   */
  Node* RecursiveDelete_(Node* node, const K& key) {
    /* key not exist */
    if (!node) {
      return nullptr;
    }

    if (key < node->key()) {
      node->set_left(RecursiveDelete_(node->left(), key));
    } else if (key > node->key()) {
      node->set_right(RecursiveDelete_(node->right(), key));
    } else {
      /* (1) is leaf */
      if (GetHeight_(node) == 0) {
        delete node;
        return nullptr;
      }
      /* (2) only right, link it up */
      if (!node->left()) {
        Node* temp = node->right();
        delete node;
        return temp;
      }
      /* (3) only left, link it up */
      if (!node->right()) {
        Node* temp = node->left();
        delete node;
        return temp;
      }
      /* (4) Complete node. Delete `node` by replacing it with the node which
        has the biggest key in the left subtree and turn to delete that node
        since it's now duplicate.
        NOTE: may also replace `node` with the smallest node from right subtree.
      */
      Node* predecessor = GetNodeWithMaxKey_(node->left());
      Node* replace = new Node{*predecessor};
      replace->set_right(node->right());
      replace->set_left(RecursiveDelete_(node->left(), predecessor->key()));
      delete node;
      node = replace;
    }

    UpdateHeight_(node);
    return MakeBalance_(node);
  }

  /** Returns the right-most node in the right subtree. */
  Node* GetNodeWithMaxKey_(Node* root) const {
    while (root->right()) {
      root = root->right();
    }
    return root;
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
      if (node->left()->left()) {
        return RightRotate_(node);
      }
      /* (2) left-right heavy: left child rotate left + `node` rotate right */
      node->set_left(LeftRotate_(node->left()));
      return RightRotate_(node);
    }

    /* right heavy */
    if (BalanceFactor_(node) < -1) {
      /* (3) right-right heavy */
      if (node->right()->right()) {
        return LeftRotate_(node);
      }
      /* (4) right-left heavy: right child rotate right + `node` rotate left */
      node->set_right(RightRotate_(node->right()));
      return LeftRotate_(node);
    }

    /* (5) already (still) balanced */
    return node;
  }

  /** Rotates `node` to the left and returns the new root. */
  Node* LeftRotate_(Node* const node) {
    Node* right_node = node->right();
    Node* right_left_node = right_node->left();
    /* Moves the right-left node to the right,
      and then `node` to the left of the right node. */
    node->set_right(right_left_node);
    right_node->set_left(node);

    /* `node` is now under the original right node, so update `node` first. */
    UpdateHeight_(node);
    UpdateHeight_(right_node);

    return right_node;
  }

  /** Rotates `node` to the right and returns the new root. */
  Node* RightRotate_(Node* const node) {
    Node* left_node = node->left();
    Node* left_right_node = left_node->right();

    /* Moves the left-right node to the left,
      and then `node` to the right of the left node. */
    node->set_left(left_right_node);
    left_node->set_right(node);

    /* `node` is now under the orignal left node, so update `node` first. */
    UpdateHeight_(node);
    UpdateHeight_(left_node);

    return left_node;
  }
};


#endif /* end of include guard: SRC_AVL_TREE_HPP_ */


/*
 * References
 *  traversals: https://shubo.io/iterative-binary-tree-traversal/
 */

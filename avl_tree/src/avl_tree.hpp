#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <stack>
#include <vector>

#include "tree_node.hpp"

// AVL tree is a highly balanced binary search tree.
// It's height h is less than 1.44lgn, where n is the number of elements.
//
// Supported operations and corresponding time complexities:
//  Search - O(lgn)
//  Insert - O(lgn)
//  Delete - O(lgn)
//  Traverse - O(n)
// No duplicate keys in the tree.
// When inserting, the original TreeNode data will be updated if key duplicates.

template<typename DataType, typename KeyType = int>
class AVLTree {
  using Node = TreeNode<DataType, KeyType>;

public:
  Node* Search(const KeyType key) const {
    Node* cur = root_;
    while (cur) {
      if (key == cur->key) {
        return cur;
      }
      else if (key < cur->key) {
        cur = cur->left;
      }
      else if (key > cur->key) {
        cur = cur->right;
      }
    }
    return nullptr;
  }

  // In-order traversal. In ascending order with respect to keys.
  std::vector<DataType> Traverse() const {
    std::vector<DataType> res;
    if (!root_) {
      return res;
    }
    // res.reserve(root_->height);
    std::stack<Node*> s;
    Node* cur = root_;
    // Go left down to leaf and then retrieve. So can touch the left first.
    while (cur || !s.empty()) {
      if (cur) {
        s.push(cur);  // wait for the retrieval
        cur = cur->left;
      }
      else {
        res.push_back(s.top()->data);  // traverse
        cur = s.top()->right;
        s.pop();
      }
    }
    return res;
  }

  // This is a in-place insertion.
  void Insert(const DataType& data, const KeyType key) {
    if (!root_) {
      root_ = new Node(data, key);
      return;
    }
    Node* par = nullptr;
    Node* cur = root_;
    // find the pos to insert
    while (cur && key != cur->key) {
      par = cur;
      if (key < cur->key) {
        cur = cur->left;
      }
      else if (key > cur->key) {
        cur = cur->right;
      }
    }
    // if key duplicates, update the data
    if (cur) {
      cur->data = data;
    }
    else if (key < par->key) {
      par->left = new Node(data, key);
    }
    else if (key > par->key) {
      par->right = new Node(data, key);
    }
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
    return node ? node.height : -1;
  }

  // height left - right
  int BalanceFactor_(const Node* const node) const {
    return node ? 0 : Height_(node.left) - Height_(node.right);
  }

  Node* root_ = nullptr;

};


#endif /* end of include guard: AVL_TREE_HPP_ */


// Resources
//  traversals: https://shubo.io/iterative-binary-tree-traversal/

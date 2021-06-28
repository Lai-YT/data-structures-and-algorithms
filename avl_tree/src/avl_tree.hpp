#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>

#include "tree_node.hpp"


template<typename DataType, typename KeyType = int>
class AVLTree {
  using Node = TreeNode<DataType, KeyType>;

public:
  // const qualifier is to prevent link-breaking from the outside.
  // Can't Search and modify the data from the outside.
  // Use Search(if found) + Insert(new_data, corresponding_key) to update data.
  const Node* Search(const KeyType key) const {
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
    std::stack<Node*> s;
    Node* cur = root_;
    // Go left down to leaf and then retrieve. So can touch the left first.
    while (cur || !s.empty()) {
      if (cur) {
        s.push(cur);  // wait for the retrieval
        cur = cur->left;
      } else {
        Node* temp = s.top();
        s.pop();
        res.push_back(temp->data);  // traverse
        cur = temp->right;
      }
    }
    return res;
  }

  // This is a in-place insertion.
  void Insert(const DataType& data, const KeyType key) {
    Node* const new_node = new Node(data, key);
    if (!root_) {
      root_ = new_node;
      return;
    }
    root_ = RecursiveInsert_(root_, new_node);
  }

  // false if try to delete non-existent Node
  bool Delete(const KeyType key) {
    if (!Search(key)) {
      return false;
    }
    root_ = RecursiveDelete_(root_, key);
    return true;
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
    node->height = std::max(Height_(node->left), Height_(node->right)) + 1;
  }

  Node* RecursiveInsert_(Node* const node, Node* const new_node) {
    // if key duplicates, just update the data
    if (new_node->key == node->key) {
      node->data = new_node->data;
      delete new_node;
      return node;
    }
    if (new_node->key < node->key) {
      if (node->left) {
        node->left = RecursiveInsert_(node->left, new_node);
      } else {
        node->left = new_node;
      }
    }
    else if (new_node->key > node->key) {
      if (node->right) {
        node->right = RecursiveInsert_(node->right, new_node);
      } else {
        node->right = new_node;
      }
    }
    UpdateHeight_(node);
    return MakeBalance_(node);
  }

  Node* RecursiveDelete_(Node* node, const KeyType key) {
    if (key < node->key) {
      node->left = RecursiveDelete_(node->left, key);
    }
    else if (key > node->key) {
      node->right = RecursiveDelete_(node->right, key);
    }
    else {
      // case 1: is leaf
      if (!Height_(node)) {
        delete node;
        return nullptr;
      }
      // case 2: only right, link it up
      else if (!node->left) {
        Node* temp = node->right;
        delete node;
        return temp;
      }
      // case 3: only left, link it up
      else if (!node->right) {
        Node* temp = node->left;
        delete node;
        return temp;
      }
      // case 4: complete node. Let the node with biggest key from the left subtree
      //         up and recursively delete it.
      else {
        Node* predecessor = GetNodeWithMaxKey_(node->left);
        node->data = predecessor->data;
        node->key = predecessor->key;
        node->left = RecursiveDelete_(node->left, predecessor->key);
      }
    }
    UpdateHeight_(node);
    return MakeBalance_(node);
  }

  Node* GetNodeWithMaxKey_(Node* root) const {
    if (root->right) {
      root = root->right;
    }
    return root;
  }

  Node* MakeBalance_(Node* const node) {
    // left too heavy
    if (BalanceFactor_(node) > 1) {
      // left-left heavy
      if (node->left->left) {
        return RightRotate_(node);
      }
      else {  // left-right heavy
        node->left = LeftRotate_(node->left);
        return RightRotate_(node);
      }
    }
    // right too high
    else if (BalanceFactor_(node) < -1) {
      // right-right heavy
      if (node->right->right) {
        return LeftRotate_(node);
      }
      else {  // right-left heavy
        node->right = RightRotate_(node->right);
        return LeftRotate_(node);
      }
    }
    return node;
  }

  Node* LeftRotate_(Node* const node) {
    Node* right_node = node->right;
    Node* right_left_node = right_node->left;

    node->right = right_left_node;
    right_node->left = node;

    // "node" is now under "right_node", so update "node" first.
    UpdateHeight_(node);
    UpdateHeight_(right_node);

    return right_node;
  }

  Node* RightRotate_(Node* const node) {
    Node* left_node = node->left;
    Node* left_right_node = left_node->right;

    node->left = left_right_node;
    left_node->right = node;

    // "node" is now under "left_node", so update "node" first.
    UpdateHeight_(node);
    UpdateHeight_(left_node);

    return left_node;
  }


  Node* root_ = nullptr;

};


#endif /* end of include guard: AVL_TREE_HPP_ */


// Resources
//  traversals: https://shubo.io/iterative-binary-tree-traversal/

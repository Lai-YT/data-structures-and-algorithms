#ifndef SRC_TREE_NODE_HPP_
#define SRC_TREE_NODE_HPP_

/**
 * Define `MEM_DEBUG` before including this file to enable the memory
 * allocation-deallocation counting feature, which can be used to test memory leaks.
 */

 #include <algorithm>


 template<typename K /* key */, typename V /* value */>
 struct KeyValuePair {
   K key;
   V value;
 };


template<typename K, typename V>
class TreeNode {
public:
  TreeNode(const KeyValuePair<K, V> p)
      : key_{p.key}, value_{p.value}, height_{0} {
#ifdef MEM_DEBUG
    ++leak_count;
#endif
  }

#ifdef MEM_DEBUG
  ~TreeNode() {
    --leak_count;
  }
#endif

  K key() const {
    return key_;
  }

  V value() const {
    return value_;
  }

  void set_value(const V& value) {
    value_ = value;
  }

  TreeNode<K, V>* left() const {
    return left_;
  }

  void set_left(TreeNode<K, V>* node) {
    left_ = node;
  }

  TreeNode<K, V>* right() const {
    return right_;
  }

  void set_right(TreeNode<K, V>* node) {
    right_ = node;
  }

  int height() const {
    return height_;
  }

  /* If we use a recursive call to really get the height of the tree node,
    the time complexity would be O(n). To solve this, we will have the tree
    maintain the height of nodes, which means tree will have to adjust height
    of all nodes affected by insertion/deletion, but still keep them O(lg(n)). */
  void set_height(int height) {
    height_ = height;
  }

#ifdef MEM_DEBUG
  static int leak_count;
#endif

private:
  K key_;
  V value_;
  int height_;
  /* not taking ownership of any of the children */
  TreeNode<K, V>* left_ = nullptr;
  TreeNode<K, V>* right_ = nullptr;
};

#ifdef MEM_DEBUG
template<typename K, typename V>
int TreeNode<K, V>::leak_count = 0;
#endif

#endif /* end of include guard: SRC_TREE_NODE_HPP_ */

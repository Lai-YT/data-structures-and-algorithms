#ifndef SRC_TREE_NODE_HPP_
#define SRC_TREE_NODE_HPP_

/**
 * Define `MEM_DEBUG` before including this file to enable the memory
 * allocation-deallocation counting feature, which can be used to test memory leaks.
 */


template<typename DataType, typename KeyType>
struct TreeNode {
  DataType data;
  KeyType key;
  int height = 0;
  /* not taking ownership of any of the children */
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;

  TreeNode(const DataType& data, const KeyType& key)
      : data(data), key(key), height(0) {
#ifdef MEM_DEBUG
    ++leak_count;
#endif
  }

#ifdef MEM_DEBUG
  ~TreeNode() {
    --leak_count;
  }
#endif

  TreeNode(const TreeNode&) = delete;
  TreeNode& operator= (const TreeNode&) = delete;

  static int leak_count;
};

#ifdef MEM_DEBUG
template<typename DataType, typename KeyType>
int TreeNode<DataType, KeyType>::leak_count = 0;
#endif

#endif /* end of include guard: SRC_TREE_NODE_HPP_ */

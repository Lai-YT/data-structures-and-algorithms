#ifndef TREE_NODE_HPP_
#define TREE_NODE_HPP_


template<typename DataType, typename KeyType = int>
struct TreeNode {
  DataType data;
  KeyType key;
  int height = 0;
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;

  TreeNode(const DataType& data, const KeyType key)
    :data(data),key(key),height(0) {
    ++count;
  }

  ~TreeNode() {
    --count;
  }

  TreeNode(const TreeNode&) = delete;
  TreeNode& operator= (const TreeNode&) = delete;

  static int count;
};

template<typename DataType, typename KeyType>
int TreeNode<DataType, KeyType>::count = 0;


#endif /* end of include guard: TREE_NODE_HPP_ */

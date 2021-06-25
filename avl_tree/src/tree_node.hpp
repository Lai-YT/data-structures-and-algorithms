#ifndef TREE_NODE_HPP_
#define TREE_NODE_HPP_

// D is data_type, K is key_type
template<typename DataType, typename KeyType = int>
struct TreeNode {
  DataType data;
  KeyType key;
  int height = 0;
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;

  TreeNode(const DataType& data, const KeyType key)
    :data(data),key(key),height(0) {}
};


#endif /* end of include guard: TREE_NODE_HPP_ */

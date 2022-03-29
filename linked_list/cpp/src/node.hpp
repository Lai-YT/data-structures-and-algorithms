#ifndef SRC_NODE_HPP_
#define SRC_NODE_HPP_


template<typename T>
struct Node {
public:
  Node(T value)
      : value(value) {}

  T value;
  Node<T>* next = nullptr;
};


#endif /* end of include guard: SRC_NODE_HPP_ */

#ifndef SRC_NODE_HPP_
#define SRC_NODE_HPP_


template<typename T>
class Node {
public:
  Node(T value)
      : value(value) {}

  /* prevent accidental modification */
  const Node<T>* next() const {
    return next_;
  }

  void SetNext(Node<T>* node) {
    next_ = node;
  }

  /* value is intentionally let public for update */
  T value;

private:
  Node<T>* next_ = nullptr;
};


#endif /* end of include guard: SRC_NODE_HPP_ */

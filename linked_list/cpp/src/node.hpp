#ifndef SRC_NODE_HPP_
#define SRC_NODE_HPP_


class Node {
public:
  Node(int value)
      : value(value) {}

  /* prevent accidental modification */
  const Node* next() const {
    return next_;
  }

  void SetNext(Node* node) {
    next_ = node;
  }

  /* value is intentionally let public for update */
  int value;

private:
  Node* next_ = nullptr;
};


#endif /* end of include guard: SRC_NODE_HPP_ */

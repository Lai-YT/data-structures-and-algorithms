#ifndef SRC_LINKED_LIST_HPP_
#define SRC_LINKED_LIST_HPP_

#include <functional>

#include "node.hpp"


template<typename T>
class LinkedList {
public:
  void Append(T data);

  void Remove(std::function<bool(T)> cond);

  Node<T>* Find(std::function<bool(T)> cond) const;

  bool IsEmpty() const;

  const Node<T>* head() const {
    return head_;
  }

  const Node<T>* tail() const {
    return tail_;
  }

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
};


#endif /* end of include guard: SRC_LINKED_LIST_HPP_ */

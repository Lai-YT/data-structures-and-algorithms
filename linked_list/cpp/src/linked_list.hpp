#ifndef SRC_LINKED_LIST_HPP_
#define SRC_LINKED_LIST_HPP_

#include <functional>

#include "node.hpp"


template<typename T>
class LinkedList {
public:
  ~LinkedList() {
    while (head_) {
      Node<T>* temp = head_;
      head_ = head_->next;
      delete temp;
      temp = nullptr;
    }
    head_ = tail_ = nullptr;
  }

  void AppendFront(T data) {

  }

  void AppendBack(T data);

  void InsertAfter(Node<T>* tar);

  void Remove(Node<T>* tar);

  Node<T>* Find(std::function<bool(T)> cond) const;

  bool IsEmpty() const {
    return head_ == nullptr;
  }

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

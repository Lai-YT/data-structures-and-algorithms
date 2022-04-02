#ifndef SRC_LINKED_LIST_HPP_
#define SRC_LINKED_LIST_HPP_

#include <cassert>
#include <functional>

#include "node.hpp"


/**
 * @brief This is a singly linked list with "head" and "tail" pointers.
 *
 * Implements the following operations:
 *  - void AppendFront(T data)
 *  - void AppendBack(T data)
 *  - void InsertAfter(Node<T>* tar, T data)
 *  - void Remove(Node<T>* tar)
 *  - Node<T>* Find(std::function<bool(T)> cond) const
 */
template<typename T>
class LinkedList {
public:
  LinkedList() = default;

  ~LinkedList() {
    while (head_) {
      Node<T>* temp = head_;
      head_ = head_->next;
      delete temp;
      temp = nullptr;
    }
    head_ = tail_ = nullptr;
  }

  /**
   * @brief Appends the data to the head of the list.
   * @complex O(1)
   */
  void AppendFront(T data) {
    auto* new_node = new Node<T>{data};
    new_node->next = head_;

    if (IsEmpty()) {
      tail_ = new_node;
    }
    head_ = new_node;
  }

  /**
   * @brief Appends the data to the tail of the list.
   * @complex O(1)
   */
  void AppendBack(T data) {
    auto* new_node = new Node<T>{data};

    if (IsEmpty()) {
      head_ = new_node;
    } else {
      tail_->next = new_node;
    }
    tail_ = new_node;
  }

  /**
   * @brief Inserts the data right after tar, tar may also be the head or tail.
   *
   * The tar can be first found by LinkedList::Find.
   *
   * @complex O(1)
   */
  void InsertAfter(Node<T>* tar, T data) {
    auto* new_node = new Node<T>{data};
    new_node->next = tar->next;
    tar->next = new_node;

    if (tar == tail_) {
      tail_ = new_node;
    }
  }

  /**
   * @brief Removes and "delete"s tar from the list if tar is in the list.
   * @complex O(n): singly linked list can't achieve O(1) since it need to find
   * the node prior to tar.
   */
  void Remove(Node<T>* tar) {
    Node<T>* cur = head_;
    Node<T>* prev = nullptr;

    while (cur && cur != tar) {
      prev = cur;
      cur = cur->next;
    }

    /* Special cases are the head and tail may be removed */

    if (!prev) {
      /* tar is the head */
      head_ = head_->next;
      /* tar is the only node in the list */
      if (cur == tail_) {
        tail_ = nullptr;
      }
    } else if (cur) {
      prev->next = cur->next;
      /* tar is the tail */
      if (cur == tail_) {
        tail_ = prev;
      }
    } else {
      return;
    }

    delete tar;
    tar = nullptr;
  }

  /**
   * @brief Finds the node which has its value meet the condition.
   * @return Node<T>: the node to find, nullptr if not found.
   * @complex O(n)
   */
  Node<T>* Find(std::function<bool(T)> cond) const {
    for (Node<T>* cur = head_; cur; cur = cur->next) {
      if (cond(cur->value)) {
        return cur;
      }
    }
    return nullptr;
  }

  bool IsEmpty() const {
    /* Head and Tail should be both null or both not null.
     * the negation makes pointer boolean
     */
    assert(!head_ == !tail_);

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

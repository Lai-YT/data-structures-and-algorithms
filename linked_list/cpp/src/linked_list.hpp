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
 *  - void Reverse()
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
   * @return Node<T>*: the node to find, nullptr if not found.
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

  /**
   * @brief Reverses the order of nodes of the list.
   * @complex O(n)
   */
  void Reverse() {
    ReverseRecursive_(head_);
  }

  /**
   * @brief The real reversal method which reverses the entire list with
   * recursive approach.
   * @complex O(n)
   */
  void ReverseRecursive_(Node<T>* node) {
    /* Every stack frame records its own "node", and when the frame is popped,
     * which is exacly in the reversed order, they link their "node" reversly.
     * After all frames are popped, the reversal is completed.
     */

    /* bounary condition: end of list, time to pop */
    if (node == tail_) {
      head_ = node;  /* original tail becomes new head */
      return;
    }

    /* go deeper */
    ReverseRecursive_(node->next);

    /* time to link reversely */
    node->next->next = node;

    /* NOTE: these only need to be done to the last node, but we re-linked the
      head pointer in early time so we can identify which one is the last */
    node->next = nullptr;
    tail_ = node;
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

#ifndef SRC_SKIP_LIST_HPP_
#define SRC_SKIP_LIST_HPP_

#define ENABLE_DEBUG 1  /* enable debug macros */

#include "debug.hpp"
#include "skip_node.hpp"


template<typename T>
class SkipList {
public:
  /**
   * @brief The probability that an inserted node be promoted.
   * 50 percent are level 1, 25 percent are level 2,
   * 12.5 percent are level 3 and so on.
   */
  static constexpr double LEVEL_UP_PROB = 0.5;

  /// The highest possible level.
  static constexpr int MAX_LEVEL = 16;

  /// Returns the node with `value` if found, otherwise nullptr.
  SkipNode<T>* Find(const T& value) const {
    const SkipNode<T>* cur = head_;

    /* from top to down */
    for (int i = level_count_; i > 0; --i) {
      /* from left to right */
      while (cur->forward(i) && cur->forward(i) < value) {
        cur = cur->forward(i);
      }
    }
    cur = cur->forward(1);

    ASSERT(!cur || cur->value() >= value);

    /*
     * We're now down to the 1st level with cur->value >= `value`,
     * so if cur->value is not equal to `value`, node with `value`
     * doesn't exist.
     */
    if (!cur || cur->value() != value) {
      return nullptr;
    }
    return const_cast<SkipNode<T>*>(cur);
  }

  void Insert(const T& value);
  void Delete(const T& value);

private:
  SkipNode<T>* head_ = new SkipNode<T>(T{/* default dummy value */}, MAX_LEVEL);
  int level_count_ = 1;  /* level starts from 1. */
};


#endif /* end of include guard: SRC_SKIP_LIST_HPP_ */

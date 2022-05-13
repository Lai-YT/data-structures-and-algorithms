#ifndef SRC_SKIP_NODE_HPP_
#define SRC_SKIP_NODE_HPP_

#include <exception>
#include <string>


class LevelRelationException : public std::runtime_error {
  using std::runtime_error::runtime_error;  /* use base class constructors */
};


/// Internal node of SkipList.
template<typename T>
class SkipNode {
public:
  /// A SkipNode has a value and knows its level.
  SkipNode(const T& value, const int level)
      : value_{value}, level_{level} {}

  T value() const {
    return value_;
  }

  int level() const {
    return level_;
  }

  /**
   * @brief The next node of the same level.
   * Node at the very right (largest value) would have its next be null.
   */
  SkipNode<T>* next() const {
    return next_;
  }

  /**
   * @throw LevelRelationException if `next` isn't at the same level.
   */
  void set_next(SkipNode<T>* const next) {
    if (next->level() != level_) {
      throw LevelRelationException("`next` node with level " + std::to_string(next->level()) + ", should be " + std::to_string(level_));
    }
    next_ = next;
  }

  /**
   * @brief The node right under this node.
   * Node at level 0 would have its `down` be null.
   */
  SkipNode<T>* down() const {
    return down_;
  }

  /**
   * @throw LevelRelationException if the level of `down` node isn't right under this node.
   */
  void set_down(SkipNode<T>* const down) {
    if (down->level() != level_ - 1) {
      throw LevelRelationException("`down` node with level " + std::to_string(down->level()) + ", should be " + std::to_string(level_ - 1));
    }
    down_ = down;
  }

private:
  T value_;
  int level_;
  SkipNode<T>* down_ = nullptr;
  SkipNode<T>* next_ = nullptr;
};


#endif /* end of include guard: SRC_SKIP_NODE_HPP_ */

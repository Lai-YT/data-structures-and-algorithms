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
      : value_{value}, level_{level}, forwards_{new SkipNode<T>*[level]} {
    /* forward nodes are automatically initialized to nullptr */
  }

  ~SkipNode() {
    delete [] forwards_;
  }

  T value() const {
    return value_;
  }

  int level() const {
    return level_;
  }

  void set_forward(SkipNode<T>* const forward, const int level) {
    if (level > level_) {
      throw LevelRelationException("level " + std::to_string(level) + " exceeds the limit, which is " + std::to_string(level_));
    }
    if (forward->level() < level) {
      throw LevelRelationException("a level " + std::to_string(level) + " forward node should have its level greater than "
                                   + std::to_string(level) + ", but only " + std::to_string(forward->level()));
    }
    forwards_[level - 1] = forward;
  }

  SkipNode<T>* forward(const int level) {
    if (level > level_) {
      throw LevelRelationException("level " + std::to_string(level) + " exceeds the limit, which is " + std::to_string(level_));
    }
    return forwards_[level - 1];
  }

private:
  T value_;
  int level_;
  /// The forward nodes pointed to in each level.
  SkipNode<T>** forwards_;
};


#endif /* end of include guard: SRC_SKIP_NODE_HPP_ */

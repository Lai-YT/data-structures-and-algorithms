#ifndef SRC_SKIP_NODE_HPP_
#define SRC_SKIP_NODE_HPP_

/**
 * Define `MEM_DEBUG` before including this file to enable the memory
 * allocation-deallocation counting feature, which can be used to test memory leaks.
 */


#include <exception>
#include <string>


/// Indicates that there's something wrong about the relation between a node and its forward node.
class LevelRelationException : public std::runtime_error {
  using std::runtime_error::runtime_error;  /* use base class constructors */
};


template<typename K /* key */, typename V /* value */>
struct KeyValuePair {
  K key;
  V value;
};


/// Internal node of SkipList.
template<typename K, typename V>
class SkipNode {
public:
  /// A SkipNode has a `value` and knows its `level`.
  SkipNode(const KeyValuePair<K, V>& p, const int level)
      : key_{p.key},
        value_{p.value},
        level_{level},
        forwards_{new SkipNode<K, V>*[level]} {
    /* initialize forward nodes to nullptr */
    for (int i = 0; i < level; ++i) {
      forwards_[i] = nullptr;
    }
#ifdef MEM_DEBUG
    ++alloc_count;
#endif
  }

#ifdef MEM_DEBUG
  /// count the number of alloc-deallocations
  static int alloc_count;
  static int dealloc_count;
#endif

  ~SkipNode() {
    /* only delete the forward containing array, not the nodes linked to */
    delete [] forwards_;
#ifdef MEM_DEBUG
    ++dealloc_count;
#endif
  }

  K key() const {
    return key_;
  }

  V value() const {
    return value_;
  }

  void set_value(const V& value) {
    value_ = value;
  }

  int level() const {
    return level_;
  }

  /**
   * @throw LevelRelationException:
   *  (1) set to a non-existing level
   *  (2) set a low level node as a high level forward node
   */
  void set_forward(SkipNode<K, V>* const forward, const int level) {
    if (level > level_) {
      throw LevelRelationException("level " + std::to_string(level) + " exceeds the limit, which is " + std::to_string(level_));
    }
    if (forward /* no check if is null */ && forward->level() < level) {
      throw LevelRelationException("a level " + std::to_string(level) + " forward node should have its level greater than "
                                   + std::to_string(level) + ", but only " + std::to_string(forward->level()));
    }
    forwards_[level - 1] = forward;
  }

  /**
   * @throw LevelRelationException: get from a non-existing level
   */
  SkipNode<K, V>* forward(const int level) const {
    if (level > level_) {
      throw LevelRelationException("level " + std::to_string(level) + " exceeds the limit, which is " + std::to_string(level_));
    }
    return forwards_[level - 1];
  }

private:
  K key_;
  V value_;
  int level_;
  /// The forward nodes pointed to in each level.
  SkipNode<K ,V>** forwards_;
};

#ifdef MEM_DEBUG
template<typename K, typename V>
int SkipNode<K, V>::alloc_count = 0;

template<typename K, typename V>
int SkipNode<K, V>::dealloc_count = 0;
#endif

#endif /* end of include guard: SRC_SKIP_NODE_HPP_ */

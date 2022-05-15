#ifndef SRC_SKIP_LIST_HPP_
#define SRC_SKIP_LIST_HPP_

#define ENABLE_DEBUG 1  /* enable debug macros */

#include <cstdlib>
#include <ctime>

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

  SkipList() {
    std::srand(std::time(0));
  }

  /// Returns the node with `value` if found, otherwise nullptr.
  SkipNode<T>* Find(const T& value) const {
    const SkipNode<T>* cur = header_;

    /* from top to down */
    for (int i = level_count_; i > 0; --i) {
      /* from left to right */
      while (cur->forward(i) && cur->forward(i)->value() < value) {
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

  void Insert(const T& value) {
    /* record our way back to update the links */
    SkipNode<T>* updates[MAX_LEVEL] = {};

    /* do a search to find the position to insert */
    SkipNode<T>* cur = header_;
    for (int i = level_count_; i > 0; --i) {
      while (cur->forward(i) && cur->forward(i)->value() < value) {
        cur = cur->forward(i);
      }
      updates[i] = cur;  /* record the way */
    }

    auto* new_node = new SkipNode<T>{value, RandomLevel_()};

    /* if the inserted node introduces a new level, we have to build them up
      and be ready to update*/
    if (new_node->level() > level_count_) {
      for (int i = level_count_ + 1; i <= new_node->level(); ++i) {
        updates[i] = header_;
      }
      level_count_ = new_node->level();
    }
    ASSERT(cur); ASSERT(new_node);  /* none of them could be null */

    /* update the links */
    for (int i = 1; i <= new_node->level(); ++i) {
      ASSERT(updates[i]);  /* not null */

      new_node->set_forward(updates[i]->forward(i), i);
      updates[i]->set_forward(new_node, i);

      ASSERT(new_node->forward(i) != new_node);  /* no cycle */
    }
  }

  void Delete(const T& value) {
    /* record our way back to update the links */
    SkipNode<T>* updates[MAX_LEVEL] = {};

    /* do a search to find the node to delete */
    SkipNode<T>* tar = header_;
    for (int i = level_count_; i > 0; --i) {
      while (tar->forward(i) && tar->forward(i)->value() < value) {
        tar = tar->forward(i);
      }
      updates[i] = tar;  /* record the way */
    }

    tar = tar->forward(1);
    if (!tar || tar->value() != value) {
      /* value not found */
      return;
    }

    /* the levels which link to `tar` need to be re-linked */
    for (int i = 1; i <= tar->level(); ++i) {
      updates[i]->set_forward(tar->forward(i), i);
    }
    delete tar;
    tar = nullptr;

    /* decrease the level count if the node with highest level is deleted */
    while (level_count_ > 1 && !header_->forward(level_count_)) {
      --level_count_;
    }
  }

  int RandomLevel_() const {
    int level = 1;
    while (level <= MAX_LEVEL && std::rand() < RAND_MAX * LEVEL_UP_PROB) {
      ++level;
    }
    ASSERT(level <= MAX_LEVEL);
    return level;
  }

private:
  SkipNode<T>* header_ = new SkipNode<T>{T{/* default dummy value */}, MAX_LEVEL};
  int level_count_ = 1;  /* level starts from 1. */
};


#endif /* end of include guard: SRC_SKIP_LIST_HPP_ */

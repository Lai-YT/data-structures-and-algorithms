#ifndef SRC_SKIP_LIST_HPP_
#define SRC_SKIP_LIST_HPP_

#ifndef ASSERT_DEBUG
  #define ASSERT_DEBUG  /* enable assertion macros */
#endif

#include <cstdlib>
#include <ctime>
#include <tuple>  /* tie */
#include <utility>  /* pair */

#include "debug.hpp"
#include "skip_node.hpp"


/**
 * @brief This is a skip list that refers to the original implementation
 * by William Pugh in "Skip Lists: A Probabilistic Alternative to Balanced Trees".
 *
 * Implements the following operations:
 *  - SkipNode<K, V>* Find(const K& key) const
 *  - void Insert(const KeyValuePair<K, V>& key_value_pair)
 *  - void Delete(const K& key)
 *
 * @note I could have use smart pointer and containers to make the resource
 * management easier and safer, but I decide to have things look pure since
 * we're now implementing the Skip List.
 */
template<typename K, typename V>
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

  ~SkipList() {
    /* deallocates node by node (from left to right) */
    SkipNode<K, V>* cur = header_;
    while (cur) {
      SkipNode<K, V>* next = cur->forward(1);
      delete cur;
      cur = next;
    }
  }

  /**
   * @brief Returns the node with `key` if found, otherwise `nullptr`.
   * @complex O(lg(n)) w.h.p.
   */
  SkipNode<K, V>* Find(const K& key) const {
    const SkipNode<K, V>* cur = header_;

    /* from top to down */
    for (int i = level_count_; i > 0; --i) {
      /* from left to right */
      while (cur->forward(i) && cur->forward(i)->key() < key) {
        cur = cur->forward(i);
      }
    }
    cur = cur->forward(1);
    ASSERT(!cur || cur->key() >= key);

    /*
     * We're now down to the 1st level with cur->key >= `key`,
     * so if cur->key is not equal to `key`, node with `key`
     * doesn't exist.
     */
    if (!cur || cur->key() != key) {
      return nullptr;
    }
    return const_cast<SkipNode<K, V>*>(cur);
  }

  /**
   * @brief Inserts a new node of key-value pair into the list. If the `key` already
   * exist, this method behaves as an Update method.
   * @complex O(lg(n)) w.h.p.
   */
  void Insert(const KeyValuePair<K, V>& key_value_pair) {
    SkipNode<K, V>** updates = nullptr;
    SkipNode<K, V>* pos = nullptr;
    std::tie(pos, updates) = FindNodeBeforeWithWayBack_(key_value_pair.key);

    /* already exist, update `value` */
    if (pos != header_ && pos->key() == key_value_pair.key) {
      pos->set_value(key_value_pair.value);
      delete [] updates;
      updates = nullptr;
      return;
    }

    auto* const new_node = new SkipNode<K, V>{key_value_pair, RandomLevel_()};

    /* if the inserted node introduces a new level, we have to build them up
      and be ready to update*/
    if (new_node->level() > level_count_) {
      for (int i = level_count_ + 1; i <= new_node->level(); ++i) {
        updates[i] = header_;
        ASSERT(!updates[i]->forward(i));  /* should points to null since is a new level */
      }
      level_count_ = new_node->level();
    }
    ASSERT(pos); ASSERT(new_node);  /* none of them could be null */

    /* update the links */
    for (int i = 1; i <= new_node->level(); ++i) {
      ASSERT(updates[i]);  /* the way we come can't be null */

      new_node->set_forward(updates[i]->forward(i), i);
      updates[i]->set_forward(new_node, i);
      ASSERT(new_node->forward(i) != new_node);  /* no cycle */
    }
    delete [] updates;
    updates = nullptr;
  }

  /**
   * @brief Deletes the node with `key` from the list if exist.
   * @complex O(lg(n)) w.h.p.
   */
  void Delete(const K& key) {
    SkipNode<K, V>** updates = nullptr;
    SkipNode<K, V>* tar = nullptr;
    std::tie(tar, updates) = FindNodeBeforeWithWayBack_(key);

    tar = tar->forward(1);  /* this is now the target node */
    if (!tar || tar->key() != key) {
      /* key not found */
      delete [] updates;
      updates = nullptr;
      return;
    }

    /* the levels which link to `tar` need to be re-linked */
    for (int i = 1; i <= tar->level(); ++i) {
      updates[i]->set_forward(tar->forward(i), i);
    }
    delete tar;
    tar = nullptr;
    delete [] updates;
    updates = nullptr;

    /* decrease the level count if the node with highest level is deleted */
    while (level_count_ > 1 && !header_->forward(level_count_)) {
      --level_count_;
    }
  }

  /**
   * @brief Generates levels randomly from level 1; level i with probability (`LEVEL_UP_PROB` ^ i).
   * i.e., a fraction `LEVEL_UP_PROB` of the nodes with level i forward nodes
   * also have level i + 1 forward nodes.
   */
  int RandomLevel_() const {
    int level = 1;
    while (level <= MAX_LEVEL && std::rand() < RAND_MAX * LEVEL_UP_PROB) {
      ++level;
    }
    ASSERT(level <= MAX_LEVEL);
    return level;
  }

  /**
   * @brief Returns the node with value just smaller than `value` and the way to the node.
   * Rememebr to delete the way back pointer array after use, the caller takes the ownership.
   * @complex O(lg(n)) w.h.p.
   */
  std::pair<SkipNode<K, V>*, SkipNode<K, V>**>
  FindNodeBeforeWithWayBack_(const K& key) const {
    /* record our way back to update the links */
    auto** way = new SkipNode<K, V>*[MAX_LEVEL];

    /* do a search to find the node */
    SkipNode<K, V>* tar = header_;
    for (int i = level_count_; i > 0; --i) {
      while (tar->forward(i) && tar->forward(i)->key() < key) {
        tar = tar->forward(i);
      }
      ASSERT(tar);
      way[i] = tar;
    }
    ASSERT(tar == header_ || tar->key() < key);  /* stop before the exact value */
    return std::make_pair(tar, way);
  }

  /**
   * @brief Prints the skip nodes level by level (no headers) for debugging purpose.
   * @complex O(n) w.h.p.
   */
  void Dump_() const {
    for (int i = level_count_; i > 0; --i) {
      SkipNode<K, V>* cur = header_->forward(i);
      std::cout << i << ": ";
      while (cur) {
        std::cout << "(" << cur->key() << ", " << cur->value() << ")" << ' ';
        cur = cur->forward(i);
      }
      std::cout << '\n';
    }
  }

private:
  SkipNode<K, V>* header_ = new SkipNode<K, V>{{K{}, V{} /* default dummy value */}, MAX_LEVEL};

  /// The level of the highest level node in the list.
  int level_count_ = 1;  /* base level starts from 1. */
};


#endif /* end of include guard: SRC_SKIP_LIST_HPP_ */

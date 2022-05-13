#ifndef SRC_SKIP_LIST_HPP_
#define SRC_SKIP_LIST_HPP_

#include "skip_node.hpp"


template<typename T>
class SkipList {
public:
  constexpr double LEVEL_UP_PROB = 0.5;
  constexpr int MAX_LEVEL = 16;

  SkipNode<T>* Find(const T& value) const;
  void Insert(const T& value);
  void Delete(const T& value);

private:

};


#endif /* end of include guard: SRC_SKIP_LIST_HPP_ */

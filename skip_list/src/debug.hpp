#ifndef SRC_DEBUG_HPP_
#define SRC_DEBUG_HPP_

#include <iostream>
#include <cstdlib>

#ifdef ENABLE_DEBUG
  #define ASSERT(condition) \
    if (!(condition)) {  \
      std::cerr << "Assertion failed: line " << __LINE__ << " file " << __FILE__ << '\n';  \
      std::abort();  \
    }
#else
  #define ASSERT(condition) ; /* replace with a single semi-colon */
#endif

#endif /* end of include guard: SRC_DEBUG_HPP_ */

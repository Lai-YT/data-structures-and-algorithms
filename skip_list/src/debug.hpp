#ifndef SRC_DEBUG_HPP_
#define SRC_DEBUG_HPP_

#include <iostream>
#include <cstdlib>

/**
 * Define `ASSERT_DEBUG` before including this file to enable the assertion feature.
 */
#ifdef ASSERT_DEBUG
  #define ASSERT(condition) \
    if (!(condition)) {  \
      std::cerr << "Assertion failed: line " << __LINE__ << " file " << __FILE__ << '\n';  \
      std::abort();  \
    }
#else
  /* replace with "nothing" to disable the assertion */
  #define ASSERT(condition)
#endif

#endif /* end of include guard: SRC_DEBUG_HPP_ */

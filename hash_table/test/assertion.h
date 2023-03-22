#include <stdio.h>

#ifndef ASSERT_EQ
#define ASSERT_EQ(actual, expected)                                      \
  if ((actual) != (expected)) {                                          \
    fprintf(stderr, "Assertion failed: %s:%d\n", __FILE__, __LINE__);    \
    fprintf(stderr, "\t" #expected " does not equal to " #actual ".\n"); \
  }
#endif

#ifndef ASSERT_TRUE
#define ASSERT_TRUE(condition)                                        \
  if (!(condition)) {                                                 \
    fprintf(stderr, "Assertion failed: %s:%d\n", __FILE__, __LINE__); \
    fprintf(stderr, "\t" #condition " does not evaluate to true.\n"); \
  }
#endif

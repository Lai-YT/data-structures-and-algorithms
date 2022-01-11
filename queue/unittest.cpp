#include "queue.hpp"

#include <gtest/gtest.h>


TEST(QueueTest, Enqueue) {
  Queue<int> q(5);
  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  ASSERT_EQ(1, q.front());
  ASSERT_EQ(3, q.size());
}


TEST(QueueTest, EnqueueAndDequeue) {
  Queue<int> q(1);
  ASSERT_EQ(0, q.size());
  for (size_t i = 0; i < 1000; i++) {
    q.Enqueue(i);
    ASSERT_EQ(i, q.front());
    ASSERT_EQ(1, q.size());
    ASSERT_FALSE(q.IsEmpty());
    q.Dequeue();
    ASSERT_EQ(0, q.size());
    ASSERT_TRUE(q.IsEmpty());
  }
}


int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

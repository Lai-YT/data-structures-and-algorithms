#include "queue.hpp"

#include <gtest/gtest.h>


TEST(CircularQueueTest, Enqueue) {
  CircularQueue<int> q(5);

  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);

  ASSERT_EQ(1, q.front());
  ASSERT_EQ(3, q.size());
}

TEST(CircularQueueTest, IsFull) {
  CircularQueue<int> q(5);

  for (size_t i = 0; i < 5; i++) {
    ASSERT_FALSE(q.IsFull());
    q.Enqueue(0);
  }
  ASSERT_TRUE(q.IsFull());
}

TEST(CircularQueueTest, EnqueueWhenFullShouldNotDequeueFront) {
  CircularQueue<int> q(5);
  for (size_t i = 0; i < 5; i++) {
    q.Enqueue(0);
  }

  q.Enqueue(1);

  ASSERT_EQ(0, q.front());
}

TEST(CircularQueueTest, EnqueueAndThenDequeue) {
  const int CAPACITY = 100;
  CircularQueue<int> q(CAPACITY);

  for (size_t i = 0; i < CAPACITY; i++) {
    q.Enqueue(i);
    ASSERT_EQ(0, q.front());
    ASSERT_EQ(i + 1, q.size());
  }
  ASSERT_TRUE(q.IsFull());
  for (size_t i = 0; i < CAPACITY; i++) {
    ASSERT_EQ(i, q.front());
    q.Dequeue();
    ASSERT_EQ(CAPACITY - (i + 1), q.size());
  }
  ASSERT_TRUE(q.IsEmpty());
}


int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

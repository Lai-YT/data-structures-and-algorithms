#ifndef QUEUE_HPP_
#define QUEUE_HPP_


template<typename T>
class CircularQueue {
public:
  CircularQueue(const int capacity)
      : buf_size_(capacity + 1), front_(0), rear_(0) {
    /* one space unused to differentiate full from empty */
    q_ = new T[buf_size_];
  }

  ~CircularQueue() {
    delete[] q_;
  }

  void Enqueue(const T& data) {
    if (!IsFull()) {
      q_[rear_] = data;
      rear_ = (rear_ + 1) % buf_size_;
    }
  }

  void Dequeue() {
    if (!IsEmpty()) {
      front_ = (front_ + 1) % buf_size_;
    }
  }

  T front() const {
      return q_[front_];
  }

  int size() const {
    return (buf_size_ + (rear_ - front_)) % buf_size_;
  }

  bool IsEmpty() const {
    return front_ == rear_;
  }

  bool IsFull() const {
    return (rear_ + 1) % buf_size_ == front_;
  }

private:
  T* q_;
  int front_;
  int rear_; /* points to the "next" space to enqueue */
  int buf_size_;
};


#endif /* end of include guard: QUEUE_HPP_ */

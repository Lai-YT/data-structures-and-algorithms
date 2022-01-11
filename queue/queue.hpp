#ifndef QUEUE_HPP_
#define QUEUE_HPP_


// this is a circular-queue
template<typename T>
class Queue {
public:
  Queue(const int capacity)
      : capacity_(capacity + 1), front_(0), rear_(0) {
    q_ = new T[capacity];
  }

  ~Queue() {
    delete[] q_;
  }

  void Enqueue(const T& data) {
    if (!IsFull()) {
      q_[rear_] = data;
      rear_ = (rear_ + 1) % capacity_;
    }
  }

  void Dequeue() {
    if (!IsEmpty()) {
      front_ = (front_ + 1) % capacity_;
    }
  }

  T front() const {
      return q_[front_];
  }

  int size() const {
    return (capacity_ + (rear_ - front_)) % capacity_;
  }

  bool IsEmpty() const {
    return front_ == rear_;
  }

  bool IsFull() const {
    return front_ - rear_ == 1;
  }

private:
  T* q_;
  int front_;
  int rear_;
  int capacity_;
};


#endif /* end of include guard: QUEUE_HPP_ */

// this is a circular-queue
template<typename T>
class Queue {
public:
  Queue(const int capacity)
  :capacity_(capacity + 1),front_(0),rear_(0) {
    q_ = new T[capacity_];
  }

  ~Queue() {
    delete[] q_;
  }

  void Enqueue(const T& data) {
    // is full
    if (front_ - rear_ == 1) return;
    q_[rear_] = data;
    rear_ = (rear_ + 1) % capacity_;
  }

  void Dequeue() {
    if (IsEmpty()) return;
    front_ = (front_ + 1) % capacity_;
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

private:
  T* q_;
  int front_;
  int rear_;
  int capacity_;
};

/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A Mutexed Queue
 */
#include <mutex>
#include <queue>

template<typename T>
class MutexQueue
{
public:
  MutexQueue()
  {}

  void push(const T& value)
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queque.push(value);
  }

  void pop()
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queque.pop();
  }

private:
    std::queue<T> m_queque;
    mutable std::mutex m_mutex;
};

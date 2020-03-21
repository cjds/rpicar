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
    m_queue.push(value);
  }

  T pop()
  {
    if (m_queue.size() >0)
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      T& result = m_queue.front();
      m_queue.pop();
      return result;
    }
    else
    {
	return static_cast<T>(0);
    }
  }

  size_t size()
  {
    return m_queue.size();
  }

private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
};

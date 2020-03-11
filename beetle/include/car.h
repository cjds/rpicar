/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A generic car class and interface that people can use
 */

#include "holster/include/error.h"

// C Standard Libs
#include <fcntl.h>
#include <unistd.h>

// C++ Standard Libs
#include <optional>
#include <tuple>
#include <string>
#include <cstring>
#include <chrono>


template<class HAL>
class Wheel
{
public:
  Wheel(const std::string& name):
  name_(name)
  {}

  /*
   * @brief Update loop for the wheel. This needs to be called at the desired rate
   */
  void update(const std::chrono::time_point<std::chrono::steady_clock>& time_point)
  {
    last_call_time = time_point;
  }

  void setSpeed(const int new_speed)
  {
    speed = new_speed;
  }

private:
  std::chrono::time_point<std::chrono::steady_clock> last_call_time;
  std::string name_;
  // Current speed you want us to spin the wheel at
  int speed;
};


template<class HAL>
class Car
{

  void update(const std::chrono::time_point<std::chrono::steady_clock>& time_point)
  {
    last_call_time = time_point;
  }
private:
  std::chrono::time_point<std::chrono::steady_clock> last_call_time;
  std::array<Wheel<HAL>, 4> wheels;
};

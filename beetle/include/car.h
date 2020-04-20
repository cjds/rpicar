/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A generic car class and interface that people can use
 */

#include "holster/include/error.h"

// C Standard Libs
#include <fcntl.h>
#include <unistd.h>

// C++ Standard Libs
#include <array>
#include <optional>
#include <tuple>
#include <string>
#include <cstring>
#include <chrono>


template<class HAL>
class Wheel
{
public:
  Wheel(const std::string& name, HAL& hal):
  name_(name),
  wheel_controller{hal}
  {}

  /*
   * @brief Update loop for the wheel. This needs to be called at the desired rate
   */
  void update(const std::chrono::time_point<std::chrono::steady_clock>& time_point)
  {
    last_call_time = time_point;
    wheel_controller.update(speed_, time_point);
  }

  void setSpeed(const int new_speed)
  {
    speed_ = new_speed;
  }

private:
  std::chrono::time_point<std::chrono::steady_clock> last_call_time;
  std::string name_;
  // Current speed you want us to spin the wheel at
  int speed_;
  HAL wheel_controller;
};


template<class HAL>
class Car
{
public:
  Car(std::array<Wheel<HAL>, 4> wheels):
  wheels{wheels}
  {}

  void update(const std::chrono::time_point<std::chrono::steady_clock>& time_point)
  {
    last_call_time = time_point;
      for (auto& wheel: wheels)
      {
        wheel.update(time_point);
      }
  }

  void setSpeed(const Vector2d& new_speed)
  {
    if (new_speed.getXMagnitude() > 0)
    {
      for (auto& wheel: wheels)
      {
	// TODO(Carl): change me
        wheel.setSpeed(1);
      }
        wheels[3].setSpeed(0);
        wheels[2].setSpeed(0);
    }
  }
private:
  std::chrono::time_point<std::chrono::steady_clock> last_call_time;
  std::array<Wheel<HAL>, 4> wheels;
};

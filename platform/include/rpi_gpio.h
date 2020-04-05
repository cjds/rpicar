/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A simple implementation for controlling the GPIO of the RPI
 */

#include "holster/include/error.h"

// C Standard Libs
#include <fcntl.h>
#include <unistd.h>

// C++ Standard Libs
#include <chrono>
#include <cstring>
#include <optional>
#include <tuple>
#include <string>

enum class Gpio
{
  PIN1 = 1,
  PIN2 = 2,
  PIN6 = 6,
  PIN13 = 13,
  PIN16 = 16,
  PIN19 = 19,
  PIN20 = 20,
  PIN21 = 21,
  PIN26 = 26,
};


enum class GpioDirection
{
  IN = 0,
  OUT = 1
};


class GpioPinControl
{
  private:
  explicit GpioPinControl(Gpio pin, int direction_filedescriptor, int value_filedescriptor):
    pin_(pin),
    direction_filedescriptor_(direction_filedescriptor),
    value_filedescriptor_(value_filedescriptor),
    exported_(true)
  {}

  public:
    static std::tuple<std::optional<Error>, std::optional<GpioPinControl>> newControl(const Gpio& pin)
    {
      // Export the desired pin by writing to /sys/class/gpio/export
      int fd = open("/sys/class/gpio/export", O_WRONLY);
      if (fd == -1) {
        return std::make_tuple(make_error("Error writing to /sys/class/gpio/export"), std::nullopt);
      }
    
      if (write(fd, std::to_string(static_cast<uint8_t>(pin)).c_str(), 2) != 2) {
        return std::make_tuple(make_error("Error writing to /sys/class/gpio/export"), std::nullopt);
      }
    
      std::string gpio_id = std::to_string(static_cast<uint8_t>(pin));
      int value_fd = open(("/sys/class/gpio/" + gpio_id + "/value").c_str(), O_WRONLY);
      if (value_fd == -1)
      {
        return std::make_tuple(make_error("Error writing to GPIO value"), std::nullopt);
      }
      int direction_fd = open(("/sys/class/gpio/" + gpio_id + "/direction").c_str(), O_WRONLY);
      if (direction_fd == -1)
      {
        return std::make_tuple(make_error("Error writing to GPIO direction"), std::nullopt);
      }
      return std::make_tuple(std::nullopt, std::optional<GpioPinControl>(GpioPinControl(pin, value_fd, direction_fd)));
    };

    Gpio getPin()
    {
      return pin_;
    }

    ~GpioPinControl()
    {
      if (exported_)
        Error("GPIO Already released").throw_error();
      close(direction_filedescriptor_);
      close(value_filedescriptor_);
    }
  
    std::optional<Error> setDirection(GpioDirection direction)
    {
      if (not exported_) return make_error("GPIO Already released");
      if (write(direction_filedescriptor_, "out", 1) != 1) {
        return make_error("Error changing description");
      }
      return std::nullopt; 
    }
  
    std::optional<Error> setValue(bool value)
    {
      if (not exported_) return make_error("GPIO Already released");
      char output_value[1] = {'1'};
      if (write(value_filedescriptor_, output_value, 3) != 3) {
        return make_error("Error setting value to file descriptor");
      }
      return std::nullopt; 
    }
  
    std::tuple<std::optional<Error>, bool> getValue()
    {
      if (not exported_) return std::make_tuple(make_error("GPIO Already released"), false);
      bool value = false;
      char value_str[3];
      if (-1 == read(value_filedescriptor_, value_str, 3)) {
        return std::make_tuple(make_error("Failed to read value!"), false);
      }
      if (std::strcmp(value_str, "1")) value = true;
      return std::make_tuple(std::nullopt, value);
    }

    std::optional<Error> release()
    {
      int fd = open("/sys/class/gpio/unexport", O_WRONLY);
      if (fd == -1) return make_error("Release failed");
      if (write(fd, std::to_string(static_cast<uint8_t>(pin_)).c_str(), 2) != 2) {
	return make_error("Writing export failed");
      }
      close(fd);
      exported_ = false;
      return std::nullopt;
    }

  private:
    const Gpio pin_;
    int direction_filedescriptor_;
    int value_filedescriptor_;
    bool exported_;
};


class RPIHal
{
 public:
  RPIHal(const GpioPinControl& input1, const GpioPinControl& input2):
    input1_(input1),
    input2_(input2)
  {}

  void update(const int speed, const std::chrono::time_point<std::chrono::steady_clock>& time_point)
  {
    last_call_time = time_point;
    // std::optional<Error> _;
    if (speed > 0) {
	input1_.setValue(1);
	input2_.setValue(0);
    }
    else if (speed < 0) {
	input1_.setValue(0);
	input2_.setValue(1);
    }
    else {
	input1_.setValue(0);
	input2_.setValue(0);
    }
  }

 private:
  GpioPinControl input1_;
  GpioPinControl input2_;
  std::chrono::time_point<std::chrono::steady_clock> last_call_time;
};


RPIHal newHal(){
  auto [error, in1 ] = GpioPinControl::newControl(Gpio::PIN26);
  auto [error2, in2 ] = GpioPinControl::newControl(Gpio::PIN19);
  return RPIHal(in1.value(), in2.value());
}

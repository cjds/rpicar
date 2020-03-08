/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A simple implementation for controlling the GPIO of the RPI
 */

#include "holster/include/error.h"
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
  PIN20 = 20,
  PIN21 = 21,
};


enum class Direction
{
  IN = 0,
  OUT = 1
};


class GpioPinControl
{
  public:
  explicit GpioPinControl(Gpio pin, int direction_filedescriptor, int value_filedescriptor):
    pin_(pin),
    direction_filedescriptor_(direction_filedescriptor),
    value_filedescriptor_(value_filedescriptor)
  {}

  Gpio getPin()
  {
    return pin_;
  }

  ~GpioPinControl()
  {
    close(direction_filedescriptor_);
    close(value_filedescriptor_);
  }

  std::optional<Error> setDirection(Direction direction)
  {
    if (write(direction_filedescriptor_, "out", 1) != 1) {
      return make_error("Error changing description");
    }
    return std::nullopt; 
  }

  std::optional<Error> setValue(bool value)
  {
    char output_value[1] = {'1'};
    if (write(value_filedescriptor_, output_value, 3) != 3) {
      return make_error("Error setting value to file descriptor");
    }
    return std::nullopt; 
  }

  std::tuple<std::optional<Error>, bool> getValue()
  {
    return std::make_tuple(std::nullopt, false);
  }

  private:
    Gpio pin_;
    int direction_filedescriptor_;
    int value_filedescriptor_;
};

std::tuple<std::optional<Error>, std::optional<GpioPinControl>> newGpioPinControl(Gpio pin)
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
  return std::make_tuple(std::nullopt, std::make_optional<GpioPinControl>(pin, value_fd, direction_fd));
};

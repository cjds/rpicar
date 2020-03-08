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
  GpioPinControl(Gpio pin):
    pin_(pin)
  {}

  Gpio getPin()
  {
    return pin_;
  }

  private:
    Gpio pin_;
};

std::tuple<std::optional<Error>, std::optional<GpioPinControl>> newGpioPinControl(Gpio pin)
{
  // Export the desired pin by writing to /sys/class/gpio/export
  int fd = open("/sys/class/gpio/export", O_WRONLY);
  if (fd == -1) {
    return std::make_tuple(std::make_optional<Error>("Error writing to /sys/class/gpio/export"), std::nullopt);
  }

  if (write(fd, std::to_string(static_cast<uint8_t>(pin)).c_str(), 2) != 2) {
    return std::make_tuple(std::make_optional<Error>("Error writing to /sys/class/gpio/export"), std::nullopt);
    perror("Error writing to /sys/class/gpio/export");
  }

  close(fd);
  return std::make_tuple(std::nullopt, std::nullopt);
};

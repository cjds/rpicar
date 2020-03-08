/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A simple implementation for controlling the GPIO of the RPI
 */

#include <optional>
#include <tuple>
#include "holster/include/error.h"

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
  return std::make_tuple(std::nullopt, std::nullopt);
};

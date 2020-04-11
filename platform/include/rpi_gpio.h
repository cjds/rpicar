/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A simple implementation for controlling the GPIO of the RPI
 */

#include "holster/include/error.h"
#include <gpiod.h>

#include <linux/gpio.h>


// C Standard Libs
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>


// C++ Standard Libs
#include <chrono>
#include <cstring>
#include <optional>
#include <tuple>
#include <string>


enum class Gpio: unsigned int
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
  explicit GpioPinControl(Gpio pin, gpiod_line *line):
    pin_(pin),
    exported_(true),
    line(line),
    pin_str_(std::to_string(static_cast<uint16_t>(pin)))
  {}

  public:
    static std::tuple<std::optional<Error>, std::optional<GpioPinControl>> newControl(const Gpio& pin)
    {
      std::string gpio_chip = "gpiochip0";
      struct gpiod_chip *chip;
      struct gpiod_line *line;

      std::string pin_str = std::to_string(static_cast<uint16_t>(pin));
      chip = gpiod_chip_open_by_name(gpio_chip.c_str());
      if (!chip) {
        return std::make_tuple(make_error("Opening chip failed"), std::nullopt);
      }
      line = gpiod_chip_get_line(chip, static_cast<unsigned int>(pin));
      if (!line) {
        return std::make_tuple(make_error("Get line failed"), std::nullopt);
      }
      return std::make_tuple(std::nullopt, std::optional<GpioPinControl>(GpioPinControl(pin, line)));
    };

    Gpio getPin()
    {
      return pin_;
    }

    ~GpioPinControl()
    {
      if (exported_) { Error("GPIO Already released").throw_error(); }
      release();
    }
  
    std::optional<Error> setDirection(GpioDirection direction)
    {
      int ret;
      if (direction == GpioDirection::IN)
      {
	ret = gpiod_line_request_output(line, pin_str_.c_str(), 0);
	if (ret < 0) {
	  return make_error("Request line as output failed\n");
	}
      }
      else if (direction == GpioDirection::OUT)
      {
	ret = gpiod_line_request_input(line, pin_str_.c_str());
	if (ret < 0) {
	  return make_error("Request line as output failed\n");
	}
      }
      return std::nullopt;
    }
  
    std::optional<Error> setValue(bool value)
    { 
      if (not exported_) return make_error("GPIO Already released");
      int ret = gpiod_line_set_value(line, value);
      if (ret < 0) {
        return make_error("Error setting value to file descriptor");
      }
      return std::nullopt; 
    }
  
    std::tuple<std::optional<Error>, bool> getValue()
    {
      int value;
      if (not exported_) return make_tuple(make_error("GPIO Already released"), false);
      value = gpiod_line_get_value(line);
      return std::make_tuple(std::nullopt, value); 
    }

    std::optional<Error> release()
    {
      gpiod_line_release(line);
      exported_ = false;
      return std::nullopt;
    }

  private:
    const Gpio pin_;
    bool exported_;
    gpiod_line* line;
    std::string pin_str_;

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


RPIHal newHal(const Gpio& p1,const Gpio& p2){
  auto [error, in1 ] = GpioPinControl::newControl(p1);
  auto [error2, in2 ] = GpioPinControl::newControl(p2);
  if(error.has_value()){
	  std::cout << error.value().getError() << std::endl;
  }
  if(error2.has_value()){
	  std::cout << error2.value().getError() << std::endl;
  }
  in1.value().setDirection(GpioDirection::OUT);
  in2.value().setDirection(GpioDirection::OUT);
  return RPIHal(in1.value(), in2.value());
}

/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A simple implementation for controlling the GPIO of the RPI
 */

#include "holster/include/error.h"
#include <gpiod.h>


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
  PIN4 = 4,
  PIN6 = 6,
  PIN13 = 13,
  PIN16 = 16,
  PIN17 = 17,
  PIN19 = 19,
  PIN20 = 20,
  PIN21 = 21,
  PIN22 = 22,
  PIN26 = 26,
  PIN27 = 27,
};


enum class GpioDirection
{
  IN = 0,
  OUT = 1
};

class GpioChip
{
public:
  static const std::tuple<std::optional<Error>, std::optional<GpioChip>> newChip(const std::string& chipname)
  {
    gpiod_chip* chip = gpiod_chip_open_by_name(chipname.c_str());
    if (!chip)
    {
      return std::make_tuple(make_error("Chip open failed"), std::nullopt);
    }
    return std::make_tuple(std::nullopt, GpioChip(gpiod_chip_open_by_name(chipname.c_str())));
    
  }

  gpiod_chip* getGpioChip() const
  {
    return chip_;
  }

  ~GpioChip()
  {
//    gpiod_chip_close(chip_);
  }

private:
  GpioChip(gpiod_chip* chip):
    chip_(chip)
  {}

  gpiod_chip* chip_;
};

class GpioPinControl
{
  private:
   GpioPinControl(Gpio pin, std::shared_ptr<gpiod_line*> line):
    pin_(pin),
    exported_(true),
    line(line),
    pin_str_(std::to_string(static_cast<uint16_t>(pin)))
   {}

  public:
    static std::tuple<std::optional<Error>, std::optional<GpioPinControl>> newControl(const Gpio& pin, const GpioChip& chip)
    {
      struct gpiod_line *line;
      std::string pin_str = std::to_string(static_cast<uint16_t>(pin));
      line = gpiod_chip_get_line(chip.getGpioChip(), static_cast<unsigned int>(pin));
      if (!line) {
        return std::make_tuple(make_error("Get line failed"), std::nullopt);
      }
      return std::make_tuple(std::nullopt, std::optional(GpioPinControl(pin, std::make_shared<gpiod_line*>(line))));
    };

    Gpio getPin()
    {
      return pin_;
    }

    ~GpioPinControl()
    {
      if (exported_) { Error("GPIO Already released").throw_error(); }
      //release();
    }
  
    std::optional<Error> setDirection(GpioDirection direction)
    {
      int ret;
      if (direction == GpioDirection::OUT)
      {
	ret = gpiod_line_request_output(*line, pin_str_.c_str(), 0);
	if (ret < 0) {
	  return make_error("Request line as output failed\n");
	}
      }
      else if (direction == GpioDirection::IN)
      {
	ret = gpiod_line_request_input(*line, pin_str_.c_str());
	if (ret < 0) {
	  return make_error("Request line as input failed\n");
	}
      }
      return std::nullopt;
    }
  
    std::optional<Error> setValue(bool value)
    { 
      if (not exported_) return make_error("GPIO Already released");
      int ret = gpiod_line_set_value(*line, value);
      if (ret < 0) {
        return make_error("Error setting value to file descriptor");
      }
      return std::nullopt; 
    }
  
    std::tuple<std::optional<Error>, bool> getValue()
    {
      int value;
      if (not exported_) return make_tuple(make_error("GPIO Already released"), false);
      value = gpiod_line_get_value(*line);
      return std::make_tuple(std::nullopt, value); 
    }

    std::optional<Error> release()
    {
      gpiod_line_release(*line);
      exported_ = false;
      return std::nullopt;
    }

  private:
    const Gpio pin_;
    bool exported_;
    std::shared_ptr<gpiod_line*> line;
    std::string pin_str_;

};


class RPIHal
{
   explicit RPIHal(const std::shared_ptr<GpioPinControl>& input1, const std::shared_ptr<GpioPinControl>& input2):
    input1_(input1),
    input2_(input2)
  {}

public:
  void update(const int speed, const std::chrono::time_point<std::chrono::steady_clock>& time_point)
  {
    last_call_time = time_point;
    if (speed != previous_speed_)
    {
      std::cout << speed << std::endl;
    if (speed > 0) {
	dieIfError(input1_->setValue(1));
	dieIfError(input2_->setValue(1));
    }
    else if (speed < 0) {
	dieIfError(input1_->setValue(1));
	dieIfError(input2_->setValue(1));
    }
    else {
	input1_->setValue(0);
	input2_->setValue(0);
    }
    previous_speed_=speed;
    }
  }


static std::tuple<std::optional<Error>, std::optional<RPIHal>> newHal(const GpioChip& chip, const Gpio& p1,const Gpio& p2){
  auto [error, in1 ] = GpioPinControl::newControl(p1, chip);
  auto [error2, in2 ] = GpioPinControl::newControl(p2, chip);
  if(error.has_value()){
	  return std::make_tuple(make_error(error.value().getError()), std::nullopt);
  }
  if(error2.has_value()){
	  return std::make_tuple(make_error(error2.value().getError()), std::nullopt);
  }
  dieIfError(in1.value().setDirection(GpioDirection::OUT));
  dieIfError(in2.value().setDirection(GpioDirection::OUT));
  return std::make_tuple(std::nullopt, RPIHal(std::make_shared<GpioPinControl>(in1.value()), std::make_shared<GpioPinControl>(in2.value())));
}
 private:
 const std::shared_ptr<GpioPinControl> input1_;
 const std::shared_ptr<GpioPinControl> input2_;
  int previous_speed_ =2;
  std::chrono::time_point<std::chrono::steady_clock> last_call_time;
};

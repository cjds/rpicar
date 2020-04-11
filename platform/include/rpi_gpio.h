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
  explicit GpioPinControl(Gpio pin):
    pin_(pin),
    exported_(true)
  {}

  public:
    static std::tuple<std::optional<Error>, std::optional<GpioPinControl>> newControl(const Gpio& pin)
    {
/*
      // Export the desired pin by writing to /sys/class/gpio/export
      std::ofstream output_file;
      output_file.open("/sys/class/gpio/export");
      if (not output_file.is_open()) {
        return std::make_tuple(make_error("Error opening /sys/class/gpio/export"), std::nullopt);
      }
      output_file << pin_str.c_str() << std::endl;
      output_file.close();

      std::ofstream value_file;
      value_file.open("/sys/class/gpio/" + pin_str + "/value");
      if (not value_file.is_open()) {
        return std::make_tuple(make_error("Error opening /sys/class/gpio/" + pin_str + "/value"), std::nullopt);
      }
      value_file << "0" << std::endl;
      value_file.close();
*/
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
      return std::make_tuple(std::nullopt, std::optional<GpioPinControl>(GpioPinControl(pin)));
    };

    Gpio getPin()
    {
      return pin_;
    }

    ~GpioPinControl()
    {
      if (exported_) { Error("GPIO Already released").throw_error(); }
    }
  
    std::optional<Error> setDirection(GpioDirection direction)
    {
      std::string pin_str = std::to_string(static_cast<uint16_t>(pin_));
      if (not exported_) return make_error("GPIO Already released");
      std::ofstream direction_file;
      direction_file.open("/sys/class/gpio/" + pin_str+ "/direction");
      if (not direction_file.is_open()) 
      {
        return make_error("Error writing to GPIO direction"); 
      }
      if (direction == GpioDirection::IN)
      {
        direction_file << "in";
      }
      else
      {
        direction_file << "out";
      }
      direction_file.close();
      return std::nullopt; 
    }
  
    std::optional<Error> setValue(bool value)
    { 
      std::string pin_str = std::to_string(static_cast<uint16_t>(pin_));
      if (not exported_) return make_error("GPIO Already released");
      /*
      char output_value[1] = {'1'};
      if (write(value_filedescriptor_, output_value, 3) != 3) {
        return make_error("Error setting value to file descriptor");
      }*/
      return std::nullopt; 
    }
  
    std::tuple<std::optional<Error>, bool> getValue()
    {
      bool value = false;
      std::string pin_str = std::to_string(static_cast<uint16_t>(pin_));
      if (not exported_) return std::make_tuple(make_error("GPIO Already released"), false);
      std::ifstream value_file;
      value_file.open("/sys/class/gpio/" + pin_str + "/value");
      char a[1];
      if (not value_file.is_open()) 
      {
        return std::make_tuple(make_error("Error writing to GPIO direction"), false); 
      }
      while(!value_file.eof())
      {
	value_file >> a;
      }
      if (std::strcmp(a, "1")) value = true;
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


RPIHal newHal(const Gpio& p1,const Gpio& p2){
  auto [error, in1 ] = GpioPinControl::newControl(p1);
  auto [error2, in2 ] = GpioPinControl::newControl(p2);
  if(error.has_value()){
	  std::cout << error.value().getError() << std::endl;
  }
  if(error2.has_value()){
	  std::cout << error2.value().getError() << std::endl;
  }
  if(in1.has_value()){
	  std::cout << "BALUE" << std::endl;
  }
  if(in2.has_value()){
	  std::cout << "BALU2E" << std::endl;
  }
  in1.value().setDirection(GpioDirection::OUT);
  in2.value().setDirection(GpioDirection::OUT);
  return RPIHal(in1.value(), in2.value());
}

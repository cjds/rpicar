/*
* @author Carl Saldanha <cjds92@gmail.com>
 */

#include "platform/include/rpi_gpio.h"
#include <thread>
#include <chrono>


int main()
{

    // 26 LED PIN
    auto [error, gpio_control ] = GpioPinControl::newControl(Gpio::PIN26);
    uint8_t number_of_times = 10;
    if (error.has_value()) return 1;
    error = gpio_control.value().setDirection(Direction::OUT);
    if (error.has_value()) return 1;
    
    for (uint8_t i=0; i< number_of_times; i++)
    {
      if (i % 2 == 0)
        error = gpio_control.value().setValue(true);
      else
        error = gpio_control.value().setValue(false);
      if (error.has_value()) return 1;
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    // And exit
    return 0;
}

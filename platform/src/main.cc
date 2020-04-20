/*
* @author Carl Saldanha <cjds92@gmail.com>
 */

#include "platform/include/rpi_gpio.h"
#include <thread>
#include <chrono>


int main()
{
    auto gc = getErrorOrDie(GpioChip::newChip("gpiochip0"));
    auto gpio_control1 = getErrorOrDie(GpioPinControl::newControl(Gpio::PIN6, gc));
    dieIfError(gpio_control1.setDirection(GpioDirection::OUT));
    auto gpio_control2 = getErrorOrDie(GpioPinControl::newControl(Gpio::PIN13, gc));
    dieIfError(gpio_control2.setDirection(GpioDirection::OUT));
    auto gpio_control3 = getErrorOrDie(GpioPinControl::newControl(Gpio::PIN19, gc));
    dieIfError(gpio_control3.setDirection(GpioDirection::OUT));
    auto gpio_control4 = getErrorOrDie(GpioPinControl::newControl(Gpio::PIN26, gc));
    dieIfError(gpio_control4.setDirection(GpioDirection::OUT));

    auto gpio_control5 = getErrorOrDie(GpioPinControl::newControl(Gpio::PIN4, gc));
    dieIfError(gpio_control5.setDirection(GpioDirection::OUT));
    auto gpio_control6 = getErrorOrDie(GpioPinControl::newControl(Gpio::PIN17, gc));
    dieIfError(gpio_control6.setDirection(GpioDirection::OUT));
    auto gpio_control7 = getErrorOrDie(GpioPinControl::newControl(Gpio::PIN27, gc));
    dieIfError(gpio_control7.setDirection(GpioDirection::OUT));
    auto gpio_control8 = getErrorOrDie(GpioPinControl::newControl(Gpio::PIN22, gc));
    dieIfError(gpio_control8.setDirection(GpioDirection::OUT));

    uint8_t number_of_times = 10;

    gpio_control1.setValue(false);
    gpio_control2.setValue(false);
    gpio_control3.setValue(false);
    gpio_control4.setValue(false);
    gpio_control5.setValue(false);
    gpio_control6.setValue(false);
    gpio_control7.setValue(false);
    gpio_control8.setValue(false);
    
    for (uint8_t i=0; i< number_of_times; i++)
    {
      if(i % 2 == 0){
        gpio_control1.setValue(true);
        gpio_control2.setValue(true);
        gpio_control3.setValue(false);
        gpio_control4.setValue(false);
        gpio_control5.setValue(true);
        gpio_control6.setValue(true);
        gpio_control7.setValue(false);
        gpio_control8.setValue(false);
      }
      else
      {
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    // And exit
    gpio_control1.setValue(false);
    gpio_control2.setValue(false);
    gpio_control3.setValue(false);
    gpio_control4.setValue(false);
    gpio_control5.setValue(false);
    gpio_control6.setValue(false);
    gpio_control7.setValue(false);
    gpio_control8.setValue(false);
    return 0;
}

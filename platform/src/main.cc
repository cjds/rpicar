/*
* @author Carl Saldanha <cjds92@gmail.com>
 */

#include "platform/include/rpi_gpio.h"
#include <thread>
#include <chrono>


int main()
{
    // 26 LED PIN
    auto [chiperr, gcopt] = GpioChip::newChip("gpiochip0");
    if (chiperr.has_value()) std::cout << chiperr.value().getError() << std::endl;
    auto gc = gcopt.value();
    auto [error1, gpio_control1 ] = GpioPinControl::newControl(Gpio::PIN6, gc);
    if (error1.has_value()) std::cout << error1.value().getError() << std::endl;
    gpio_control1.value().setDirection(GpioDirection::OUT);
    auto [error2, gpio_control2 ] = GpioPinControl::newControl(Gpio::PIN13, gc);
    gpio_control2.value().setDirection(GpioDirection::OUT);
    auto [erro3, gpio_control3 ] = GpioPinControl::newControl(Gpio::PIN19, gc);
    gpio_control3.value().setDirection(GpioDirection::OUT);
    auto [error4, gpio_control4 ] = GpioPinControl::newControl(Gpio::PIN26, gc);
    gpio_control4.value().setDirection(GpioDirection::OUT);


    auto [error5, gpio_control5 ] = GpioPinControl::newControl(Gpio::PIN6, gc);
    gpio_control5.value().setDirection(GpioDirection::OUT);
    auto [error6, gpio_control6 ] = GpioPinControl::newControl(Gpio::PIN13, gc);
    gpio_control6.value().setDirection(GpioDirection::OUT);
    auto [error7, gpio_control7 ] = GpioPinControl::newControl(Gpio::PIN19, gc);
    gpio_control7.value().setDirection(GpioDirection::OUT);
    auto [error8, gpio_control8 ] = GpioPinControl::newControl(Gpio::PIN26, gc);
    gpio_control8.value().setDirection(GpioDirection::OUT);

    uint8_t number_of_times = 10;
    
    for (uint8_t i=0; i< number_of_times; i++)
    {
      if (i % 2 == 0){
        auto error = gpio_control1.value().setValue(true);
	if (error.has_value()) std::cout << "IMOITNDODITNOE" << std::endl;
        gpio_control2.value().setValue(true);
        gpio_control3.value().setValue(false);
        gpio_control4.value().setValue(false);
        gpio_control5.value().setValue(true);
        gpio_control6.value().setValue(true);
        gpio_control7.value().setValue(false);
        gpio_control8.value().setValue(false);
      }
      else
      {
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    // And exit
    gpio_control1.value().setValue(false);
    gpio_control2.value().setValue(false);
    gpio_control3.value().setValue(false);
    gpio_control4.value().setValue(false);
    gpio_control5.value().setValue(false);
    gpio_control6.value().setValue(false);
    gpio_control7.value().setValue(false);
    gpio_control8.value().setValue(false);
    return 0;
}

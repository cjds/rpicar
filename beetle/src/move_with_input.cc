/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief Move car using input from  the user
 */

#include "holster/include/mutex_queue.h"
#include "holster/include/vector.h"
#include "platform/include/rpi_gpio.h"
#include "beetle/include/car.h"
#include <array>
#include <thread>
#include <chrono>
#include <iostream>
#include <signal.h>
#include <functional>


const std::string ask_question(const std::string& question)
{
  std::string input_string;
  std::cout << question.c_str() << ": ";
  std::getline(std::cin, input_string);
  return input_string;
}


const bool compare_string_case_insensitive(const std::string& str1, const std::string& str2)
{
  return str1.size() == str2.size() && std::equal(str1.begin(), str1.end(), str2.begin(), [](auto a, auto b){return std::tolower(a)==std::tolower(b);});
}

void user_input_thread(int& stop, MutexQueue<Vector2d>& command_queue)
{
  using namespace std::chrono_literals;
  while (!stop)
  {
    std::string output = ask_question("How do you want to move");
    if (compare_string_case_insensitive("W", output))
    {
	command_queue.push(Vector2d(1,0));
    }
    else if (compare_string_case_insensitive("A", output))
    {
	command_queue.push(Vector2d(0,1));
    }
    else if (compare_string_case_insensitive("S", output))
    {
	command_queue.push(Vector2d(-1,0));
    }
    else if (compare_string_case_insensitive("D", output))
    {
	command_queue.push(Vector2d(-1,0));
    }
    else
    {
      std::cout << "Wrong move cowboy" << std::endl;
    }

    std::this_thread::sleep_for(2ms);
  }
}

void car_thread(int& stop, MutexQueue<Vector2d>& command_queue)
{
  auto [chiperr, gcopt] = GpioChip::newChip("gpiochip0");
  if (chiperr.has_value()) std::cout << chiperr.value().getError() << std::endl;
  auto gc = gcopt.value();
  using namespace std::chrono_literals;
  auto [error, rpi_f_left] = RPIHal::newHal(gc, Gpio::PIN6, Gpio::PIN19);
  auto [error2, rpi_f_right] = RPIHal::newHal(gc, Gpio::PIN4, Gpio::PIN17);
  auto [error3, rpi_b_left] = RPIHal::newHal(gc, Gpio::PIN13, Gpio::PIN26);
  auto [error4, rpi_b_right] = RPIHal::newHal(gc, Gpio::PIN22, Gpio::PIN27);
  std::array<Wheel<RPIHal>, 4> wheels{Wheel("f_left", rpi_f_left.value()),
  Wheel("f_right", rpi_f_right.value()),
  Wheel("b_left", rpi_b_left.value()),
  Wheel("b_right", rpi_b_right.value())};
  Car<RPIHal> c{wheels};
  Vector2d current_command{0, 0};
  while (!stop)
  {
    if (command_queue.size() > 0)
    {
      std::optional<Vector2d> queued= command_queue.pop();
      if(queued.has_value())
      {
	current_command = queued.value();
        std::cout << current_command.to_str() << std::endl;
      }
    }
    std::this_thread::sleep_for(2ms);
    c.setSpeed(current_command);
    c.update(std::chrono::time_point<std::chrono::high_resolution_clock>());

  }
}

std::function<void(int)> shutdown_handler;
void signal_handler(int signal) { shutdown_handler(signal); }

int main()
{
  MutexQueue<Vector2d> command_queue;
  int stop = 0;
  signal(SIGINT, signal_handler);
  shutdown_handler = [&stop](int signum){
    stop = 1;
  };
  std::thread t1(car_thread, std::ref(stop), std::ref(command_queue));
  std::thread t2(user_input_thread, std::ref(stop), std::ref(command_queue));
  t1.join();
  t2.join();
}

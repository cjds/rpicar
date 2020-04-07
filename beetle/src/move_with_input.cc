/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief Move car using input from  the user
 */

#include "holster/include/mutex_queue.h"
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

void user_input_thread(int& stop, MutexQueue<uint8_t>& command_queue)
{
  using namespace std::chrono_literals;
  while (!stop)
  {
    std::string output = ask_question("How do you want to move");
    if (compare_string_case_insensitive("W", output))
    {
	command_queue.push(1);
    }
    else if (compare_string_case_insensitive("A", output))
    {
	command_queue.push(2);
    }
    else if (compare_string_case_insensitive("S", output))
    {
	command_queue.push(3);
    }
    else if (compare_string_case_insensitive("D", output))
    {
	command_queue.push(4);
    }
    else
    {
      std::cout << "Wrong move cowboy" << std::endl;
    }

    std::this_thread::sleep_for(2ms);
  }
}

void car_thread(int& stop, MutexQueue<uint8_t>& command_queue)
{
  using namespace std::chrono_literals;
  std::array<Wheel<RPIHal>, 4> wheels{Wheel("f_left", newHal(Gpio::PIN6, Gpio::PIN26)),
  Wheel("f_right", newHal(Gpio::PIN16, Gpio::PIN19)),
  Wheel("b_left", newHal(Gpio::PIN20, Gpio::PIN21)),
  Wheel("b_right", newHal(Gpio::PIN21, Gpio::PIN6))};
  Car<RPIHal> c{wheels};
  while (!stop)
  {
    if (command_queue.size() > 0) std::cout << std::to_string(command_queue.pop()) << std::endl;
    std::this_thread::sleep_for(2ms);
  }
}

std::function<void(int)> shutdown_handler;
void signal_handler(int signal) { shutdown_handler(signal); }

int main()
{
  MutexQueue<uint8_t> command_queue;
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

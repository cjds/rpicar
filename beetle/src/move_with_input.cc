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

using Command = std::tuple<Vector2d, std::chrono::time_point<std::chrono::steady_clock>>;

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

void user_input_thread(int& stop, MutexQueue<Command>& command_queue)
{
  using namespace std::chrono_literals;
  while (!stop)
  {
    std::string output = ask_question("How do you want to move");
    if (compare_string_case_insensitive("W", output))
    {
	command_queue.push(std::make_tuple(Vector2d(1, 0), std::chrono::steady_clock::now()));
    }
    else if (compare_string_case_insensitive("A", output))
    {
	command_queue.push(std::make_tuple(Vector2d(0, 1), std::chrono::steady_clock::now()));
    }
    else if (compare_string_case_insensitive("S", output))
    {
	command_queue.push(std::make_tuple(Vector2d(-1, 0), std::chrono::steady_clock::now()));
    }
    else if (compare_string_case_insensitive("D", output))
    {
	command_queue.push(std::make_tuple(Vector2d(0, -1), std::chrono::steady_clock::now()));
    }
    else
    {
      std::cout << "Wrong move cowboy" << std::endl;
    }

    std::this_thread::sleep_for(2ms);
  }
}

void car_thread(int& stop, MutexQueue<Command>& command_queue)
{
  using namespace std::chrono_literals;
  auto gc = getErrorOrDie(GpioChip::newChip("gpiochip0"));
  // Front Right Wheel
  auto rpi_f_right = getErrorOrDie(RPIHal::newHal(gc, Gpio::PIN6, Gpio::PIN13));
  // Front left wheel
  auto rpi_f_left = getErrorOrDie(RPIHal::newHal(gc, Gpio::PIN26, Gpio::PIN19));
  auto rpi_b_right = getErrorOrDie(RPIHal::newHal(gc, Gpio::PIN22, Gpio::PIN27));
  auto rpi_b_left= getErrorOrDie(RPIHal::newHal(gc, Gpio::PIN4, Gpio::PIN17));
  std::array<Wheel<RPIHal>, 4> wheels{Wheel("f_left", rpi_f_left),
    Wheel("f_right", rpi_f_right),
    Wheel("b_left", rpi_b_left),
    Wheel("b_right", rpi_b_right)};
  Car<RPIHal> c{wheels};
  Vector2d current_speed{0, 0};
  std::chrono::time_point<std::chrono::steady_clock> last_time_point = std::chrono::steady_clock::now();
  while (!stop)
  {
    if (command_queue.size() > 0)
    {
      std::optional<Command> queued= command_queue.pop();
      if(queued.has_value())
      {
	current_speed = std::get<0>(queued.value());
	last_time_point = std::get<1>(queued.value());
      }
    }
    if (std::chrono::steady_clock::now() - last_time_point > 500ms)
    {
      c.setSpeed(Vector2d{0,0});
    }
    else
    {
      c.setSpeed(current_speed);
    }
    std::this_thread::sleep_for(2ms);
    c.update(std::chrono::steady_clock::now());
  }
}

std::function<void(int)> shutdown_handler;
void signal_handler(int signal) { shutdown_handler(signal); }

int main()
{
  MutexQueue<Command> command_queue;
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

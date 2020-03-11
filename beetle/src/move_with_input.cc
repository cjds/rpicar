/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief Move car using input from  the user
 */

#include "holster/include/mutex_queue.h"
#include "beetle/include/car.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <signal.h>

volatile sig_atomic_t stop;

const std::string ask_question(const std::string& question)
{
  std::string input_string;
  std::cout << question.c_str() << ": ";
  std::getline(std::cin, input_string);
  return input_string;
}

void inthand(int signum) {
  stop = 1;
}

const bool compare_string_case_insensitive(const std::string& str1, const std::string& str2)
{
  return str1.size() == str2.size() && std::equal(str1.begin(), str1.end(), str2.begin(), [](auto a, auto b){return std::tolower(a)==std::tolower(b);});
}

void user_input_thread(MutexQueue<uint8_t>& command_queue)
{

  while (!stop)
  {
    std::string output = ask_question("How do you want to move");
    if (compare_string_case_insensitive("W", output))
    {
    }
    else if (compare_string_case_insensitive("A", output))
    {
    }
    else if (compare_string_case_insensitive("S", output))
    {
    }
    else if (compare_string_case_insensitive("D", output))
    {
    }
    else
    {
      std::cout << "Wrong move cowboy" << std::endl;
    }
  }
}

void car_thread(MutexQueue<uint8_t>& command_queue)
{
}
int main()
{
  std::unique_ptr<MutexQueue<uint8_t>> command_queue = std::make_unique<MutexQueue<uint8_t>>();
  signal(SIGINT, inthand);
  std::thread t1(car_thread, command_queue);
  std::thread t2(user_input_thread, command_queue);
  t1.join();
  t2.join();
}

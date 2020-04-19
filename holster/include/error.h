/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief An error handler
 */

#ifndef HOLSTER_INCLUDE_ERROR
#define HOLSTER_INCLUDE_ERROR

#include <iostream>
#include <optional>
#include <string>
#include <tuple>


class Error
{
  public:
    explicit Error(const std::string& error):
    error_(error)
    {}

    const char* throw_error()  const throw()
    {
      return error_.c_str();
    }

    std::string getError() const
    {
      return error_;
    }

  private:
    std::string error_;
};

const std::optional<Error> make_error(const std::string& error_str)
{
  return std::make_optional<Error>(error_str);
}


void dieIfError(const std::optional<Error>& error)
{
  if (error.has_value())
  {
    std::cout << error.value().getError() << std::endl;
    exit(1);
  }
}

template<class T>
T getErrorOrDie(const std::tuple<std::optional<Error>, std::optional<T>>& error_obj)
{
  dieIfError(std::get<0>(error_obj));
  return std::get<1>(error_obj).value();
}
#endif // HOLSTER_INCLUDE_ERROR


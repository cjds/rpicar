/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief An error handler
 */

#ifndef HOLSTER_INCLUDE_ERROR
#define HOLSTER_INCLUDE_ERROR

#include <optional>
#include <string>


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

#endif // HOLSTER_INCLUDE_ERROR


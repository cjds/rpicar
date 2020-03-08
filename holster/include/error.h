#include <string>
#include <optional>


class Error
{
  public:
    explicit Error(const std::string& error):
    error_(error)
    {}

  private:
    std::string error_;
};

const std::optional<Error> make_error(const std::string& error_str)
{
  return std::make_optional<Error>(error_str);
}

#include <string>


class Error
{
  public:
    explicit Error(const std::string& error):
    error_(error)
    {}

  private:
    std::string error_;
};


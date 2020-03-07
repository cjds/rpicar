#include <string>

class Error
{
  Error(const std::string& error):
  error_(error)
  {
  }

  private:
    std::string error_;
};


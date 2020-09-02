/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A socket manager
 */

#ifndef HOLSTER_INCLUDE_SOCKET_MAKER
#define HOLSTER_INCLUDE_SOCKET_MAKER

#include <cstdlib>
#include "error.h"
#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>


class SocketHolder
{
  public:
    static std::optional<Error> createMapStateMachine(const std::string& file_name, int number_of_bytes)
    {
      boost::iostreams::mapped_file mmap(file_name.c_str(), boost::iostreams::mapped_file::readonly);
      return Error{"SSSSSSSSS"};
    }
  private:
    explicit MmapStateMachine(boost::iostreams::mapped_file_source& file)
    {
      
    }

    ~MmapStateMachine()
    {
      file_.close();
    }

    void pump()
    {
    }

  private:
    boost::iostreams::mapped_file_source file_;
    std::string error_;
};
#endif // HOLSTER_INCLUDE_SOCKET_MAKER


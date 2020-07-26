/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A shared memory manager
 */

#ifndef HOLSTER_INCLUDE_SHARED_MEMORY_MANAGER
#define HOLSTER_INCLUDE_SHARED_MEMORY_MANAGER

#include <cstdlib>
#include "error.h"
#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>


class MmapStateMachine
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
#endif // HOLSTER_INCLUDE_SHARED_MEMORY_MANAGER


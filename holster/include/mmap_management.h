/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A memory management manager
 */

#ifndef HOLSTER_INCLUDE_MMAP_MANAGEMENT
#define HOLSTER_INCLUDE_MMAP_MANAGEMENT

#include "error.h"
#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>


class MmapStateMachine
{
  public:
    static std::optional<Error> createMapStateMachine(const std::string& file_name, int number_of_bytes)
    {

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
#endif // HOLSTER_INCLUDE_MMAP_MANAGEMENT


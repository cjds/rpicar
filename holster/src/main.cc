/*
* @author Carl Saldanha <cjds92@gmail.com>
 */

#include "holster/include/mmap_management.h"
#include <thread>
#include <chrono>


int main()
{
    auto t = MmapStateMachine::createMapStateMachine("/tmp/daygeek.txt", 5);
    return 0;
}

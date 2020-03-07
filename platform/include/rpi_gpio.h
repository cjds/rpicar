/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief A simple implementation for controlling the GPIO of the RPI
 */

#include "holster/include/error.h"


enum class GPIO{
  GPIO1 = 1,
  GPIO2 = 2,
  GPIO6 = 6,
  GPIO13 = 13,
  GPIO16 = 16,
  GPIO20 = 20,
  GPIO21 = 21,
};

enum class Direction
{
  IN = 0,
  OUT = 1
};

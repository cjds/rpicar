/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief Some basic Vector operations
 */

#ifndef HOLSTER_INCLUDE_VECTOR
#define HOLSTER_INCLUDE_VECTOR

#include <optional>
#include <string>


class Vector2d
{
  public:
    explicit Vector2d(const double x_magnitude, const double y_magnitude):
    x_magnitude_(x_magnitude),
    y_magnitude_(y_magnitude)
    {}

    double getXMagnitude() const
    {
       return x_magnitude_;
    }

    double getYMagnitude() const
    {
       return y_magnitude_;
    }

    std::string to_str() const
    {
	return "X ->" + std::to_string(x_magnitude_) + "Y ->" + std::to_string(y_magnitude_);
    }
  private:
    double x_magnitude_;
    double y_magnitude_;
   
};

#endif // HOLSTER_INCLUDE_VECTOR


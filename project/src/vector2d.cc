#include "vector2d.h"

namespace csci3081
{

  Vector2D::Vector2D()
  {
    velocity_.push_back(0.0);
    velocity_.push_back(0.0);
    position_.push_back(0.0);
    position_.push_back(0.0);
  }

  Vector2D::Vector2D(std::vector<float> position, std::vector<float> velocity)
  {
    velocity_ = velocity;
    position_ = position;
    direction_ = GetUnitVector();
  }

  const std::vector<float> Vector2D::GetUnitVector()
  {
    std::vector<float> direction;

    float divisor = CalculateMagnitude();

    for (auto element : GetVelocity())
    {
      float norm_element = element / divisor;
      direction.push_back(norm_element);
    }

    return direction;
  }

  float Vector2D::CalculateMagnitude()
  {
    float sum = 0.0;
    for (auto element : velocity_)
    {
      float squared = element * element;
      sum = sum + squared;
    }
    float divisor = sqrt(sum);
    return divisor;
  }

  const std::vector<float>& Vector2D::GetVelocity() const
  {
    return velocity_;
  }

  const std::vector<float>& Vector2D::GetPosition() const
  {
    return position_;
  }

  const std::vector<float> &Vector2D::GetDirection()
  {
    return direction_;
  }

  void Vector2D::SetVelocity(std::vector<float> newVelocity)
  {
    velocity_ = newVelocity;
    direction_ = GetUnitVector();
  }

  void Vector2D::SetPosition(std::vector<float> newPosition)
  {
    position_ = newPosition;
  }

}

#include "vector3d.h"
#include <math.h>
#include <iostream>

namespace csci3081
{

  Vector3D::Vector3D(std::vector<float> position, std::vector<float> velocity)
  {
    velocity_ = velocity;
    position_ = position;
    direction_ = GetUnitVector();
  }

  const std::vector<float> Vector3D::GetUnitVector()
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

  float Vector3D::CalculateMagnitude()
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

  const std::vector<float>& Vector3D::GetVelocity()
  {
    return velocity_;
  }

  const std::vector<float>& Vector3D::GetPosition()
  {
    return position_;
  }

  const std::vector<float>& Vector3D::GetDirection()
  {
    return direction_;
  }

  void Vector3D::SetVelocity(std::vector<float> newVelocity) {
    velocity_ = newVelocity;
    direction_ = GetUnitVector();
  }

  void Vector3D::SetPosition(std::vector<float> newPosition) {
    position_ = newPosition;
  }

  std::vector<float> Vector3D::AddTwoVectors(std::vector<float> &oneVector, std::vector<float> &secondVector) {
    std::vector<float> toReturn = {0,0,0};
    int i = 0;
    for(float elemOne : oneVector) {
      float elemTwo = secondVector.at(i);
      float summedFloats = elemOne + elemTwo;
      toReturn.at(i) = summedFloats;
      i = i + 1;
    }
    return toReturn;
  }

  std::vector<float> Vector3D::SubtractTwoVectors(std::vector<float> &oneVector, std::vector<float> &secondVector) {
    std::vector<float> toReturn = {0, 0, 0};
    int i = 0;
    for (float elemOne : oneVector)
    {
      float elemTwo = secondVector.at(i);
      float subtractedFloats = elemOne - elemTwo;
      toReturn.at(i) = subtractedFloats;
      i = i + 1;
    }
    return toReturn;
  }

  std::vector<float> Vector3D::MultiplyVectorWithFloat(std::vector<float> &oneVector, float coeff) {
    std::vector<float> toReturn = {0,0,0};
    int i = 0;
    for (float elemOne : oneVector)
    {
      float multipliedElem = elemOne * coeff;
      toReturn.at(i) = multipliedElem;
      i = i + 1;
    }
    return toReturn;
  }

}

#include "vector3d.h"
#include <math.h>
#include <iostream>

namespace csci3081
{

  Vector3D::Vector3D(std::vector<float>& vector3d)
  {
    vector_ = vector3d;
  }

  const std::vector<float>& Vector3D::GetVector()
  {
    return vector_;
  }

  void Vector3D::SetVector(std::vector<float> &newVector) {
    vector_ = newVector;
  }

  void Vector3D::Normalize()
  {
    float divisor = CalculateMagnitude();

    int i = 0;
    for (float element : vector_)
    {
      vector_.at(i) = element / divisor;
      i = i + 1;
    }
  }

  float Vector3D::CalculateMagnitude()
  {
    float sum = 0.0;
    for (auto element : vector_)
    {
      float squared = element * element;
      sum = sum + squared;
    }
    float divisor = sqrt(sum);
    return divisor;
  }

  std::vector<float> Vector3D::AddTwoVectors(std::vector<float>&firstVector, std::vector<float> &anotherVector)
  {
    std::vector<float> toReturn = {0,0,0};
    int i = 0;
    for(float elemOne : firstVector) {
      float elemTwo = anotherVector.at(i);
      float summedFloats = elemOne + elemTwo;
      toReturn.at(i) = summedFloats;
      i = i + 1;
    }
    return toReturn;
  }

  std::vector<float> Vector3D::SubtractTwoVectors(std::vector<float> &firstVector, std::vector<float> &anotherVector)
  {
    std::vector<float> toReturn = {0, 0, 0};
    int i = 0;
    for (float elemOne : firstVector)
    {
      float elemTwo = anotherVector.at(i);
      float subtractedFloats = elemOne - elemTwo;
      toReturn.at(i) = subtractedFloats;
      i = i + 1;
    }
    return toReturn;
  }

  std::vector<float> Vector3D::MultiplyVectorWithFloat(std::vector<float> &firstVector, float coeff)
  {
    std::vector<float> toReturn = {0,0,0};
    int i = 0;
    for (float elemOne : firstVector)
    {
      float multipliedElem = elemOne * coeff;
      toReturn.at(i) = multipliedElem;
      i = i + 1;
    }
    return toReturn;
  }
}

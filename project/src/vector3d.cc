#include "vector3d.h"
#include <math.h>
#include <iostream>

namespace csci3081
{

  Vector3D::Vector3D(std::vector<float> vector3d)
  {
    vector_ = vector3d;
  }

  const std::vector<float> GetVector()
  {
    return vector_;
  }

  const std::vector<float> Vector3D::Normalize()
  {
    std::vector<float> direction;
    float divisor = CalculateMagnitude();

    for (auto element : vector_)
    {
      float norm_element = element / divisor;
      direction.push_back(norm_element);
    }

    return direction;
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

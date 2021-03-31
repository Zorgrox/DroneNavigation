#include "vector2d.h"

namespace csci3081
{

  Vector2D::Vector2D(std::vector<float> &vector2d)
  {
    vector_ = vector2d;
  }

  const std::vector<float> &Vector2D::GetVector()
  {
    return vector_;
  }

  void Vector2D::SetVector(std::vector<float> &newVector)
  {
    vector_ = newVector;
  }

  void Vector2D::Normalize()
  {
    // std::vector<float> direction;
    float divisor = CalculateMagnitude();

    int i = 0;
    for (float element : vector_)
    {
      if (i != 1) {
        vector_.at(i) = element / divisor;
      }
      i = i + 1;
    }
  }

  float Vector2D::CalculateMagnitude()
  {
    float sum = 0.0;
    int i = 0;
    for (auto element : vector_)
    {
      float squared = element * element;
      if (i != 1) {
        // we do not include the y coordinate in calculating the magnitude, bc that is always going to be the same?
        sum = sum + squared;
      }
      i = i + 1;
    }
    float divisor = sqrt(sum);
    return divisor;
  }

  std::vector<float> Vector2D::AddTwoVectors(std::vector<float> &firstVector, std::vector<float> &anotherVector)
  {
    std::vector<float> toReturn = {0, 0, 0};
    int i = 0;
    for (float elemOne : firstVector)
    {
      float elemTwo = anotherVector.at(i);
      float summedFloats = elemOne + elemTwo;
      toReturn.at(i) = summedFloats;
      i = i + 1;
    }
    return toReturn;
  }

  std::vector<float> Vector2D::SubtractTwoVectors(std::vector<float> &firstVector, std::vector<float> &anotherVector)
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

  std::vector<float> Vector2D::MultiplyVectorWithFloat(std::vector<float> &firstVector, float coeff)
  {
    std::vector<float> toReturn = {0, 0, 0};
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

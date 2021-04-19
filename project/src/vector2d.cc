#include "vector2d.h"
#include <math.h>

namespace csci3081
{

  Vector2D::Vector2D(std::vector<float> adr)
  {
    vector_ = adr;
  }

  const std::vector<float>& Vector2D::GetVector()
  {
    return vector_;
  }

  void Vector2D::SetVector(std::vector<float> &newVector) {
    vector_ = newVector;
  }

  void Vector2D::Normalize()
  {
    // normalizes the x and z dimensions of the address stored based on the CalculateMagnitude() magnitude of x and z dimensions
    // the y (2nd) index of the vector is zeroed because it is ignored in CalculateMagnitude() and unchanged in the motion of 2D entities, not able to be a direction component
    float divisor = CalculateMagnitude();
    vector_[0] = vector_[0]/divisor;
    vector_[1] = 0.0;
    vector_[2] = vector_[2]/divisor;
  }

  float Vector2D::CalculateMagnitude()
  {
    // adds the square of each float to the accumulator and returns the square root of the accumulator
    // 2nd index is ignored in vector2D because the entity can only move in a 2d plane of x and z instead or x, y, z
    float acc = 0.0;
    acc = (vector_[0] * vector_[0]);
    acc = acc + (vector_[2] * vector_[2]);
    return sqrt(acc);
  }

   std::vector<float> Vector2D::AddTwoVectors(std::vector<float>& adr1, std::vector<float>& adr2)
  {
    // adds the two vectors, because we want height to be unaffected the 2nd float of address1 is passed
    // into the return vector
    std::vector<float> toReturn = {0,0,0};
    toReturn[0] = adr1[0] + adr2[0];
    toReturn[1] = adr1[1];
    toReturn[2] = adr1[2] + adr2[2];
    return toReturn;
  }

   std::vector<float> Vector2D::SubtractTwoVectors(std::vector<float> &adr1, std::vector<float> &adr2)
  {
    // subtracts the two vectors, because we want height to be unaffected the 2nd float of address1 is passed
    // into the return vector
    std::vector<float> toReturn = {0,0,0};
    toReturn[0] = adr1[0] - adr2[0];
    // toReturn[1] = adr1[1];
    toReturn[2] = adr1[2] - adr2[2];
    return toReturn;
  }

   std::vector<float> Vector2D::MultiplyVectorWithFloat(std::vector<float> &adr, float scalar)
  {
    // multiplies each movement axis with the inputted scalar and returns the result, the 2nd index is not multiplied
    // because entities using this class can only move in 2D, the 2nd index is passed into the return vector
    // so that the height is unaffected
    std::vector<float> toReturn = {0,0,0};
    toReturn[0] = adr[0] * scalar;
    toReturn[1] = adr[1];
    toReturn[2] = adr[2] * scalar;
    return toReturn;
  }
}

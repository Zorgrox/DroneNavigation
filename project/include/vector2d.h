/**
 * @file vector2d.h
 */
#ifndef VECTOR2D_H_
#define VECTOR2D_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>
#include <string>

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the Vector2D class that stores both the velocity and position.
 *
 * This class has the two (x,z) dimensions. It is unused in iteration 1. It will be used for the robot and truck classes in iteration 2.
 */

  class Vector2D
  {
  public:
    /**
   * @brief Constructor: set up a Vector2D
   */
    Vector2D(std::vector<float> vector2d);

    /**
   *  This function returns the vector
   */
    const std::vector<float> &GetVector();

    /**
   *  This function sets the vector to a new vector
   */
    void SetVector(std::vector<float> &newVector);

    /**
   *  This function returns the normalized version of the vector
   */
    void Normalize();

    /**
   *  This function calculates the magnitude of the velocity (which is equivalent to the speed)
   */
    float CalculateMagnitude();

    /**
   *  This function should be used to add two standard vectors with each other
   */
    std::vector<float> AddTwoVectors(std::vector<float> &oneVector, std::vector<float> &secondVector);
    /**
   *  This function should be used to subtract two standard vectors from each other
   */
    std::vector<float> SubtractTwoVectors(std::vector<float> &oneVector, std::vector<float> &secondVector);
    /**
   *  This function should be used to multiple a vector with a float
   */
    std::vector<float> MultiplyVectorWithFloat(std::vector<float> &oneVector, float coeff);

  private:
    std::vector<float> vector_;
  };

} // namespace csci3081

#endif // VECTOR2D_H_

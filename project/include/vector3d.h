/**
 * @file vector3d.h
 */
#ifndef VECTOR3D_H_
#define VECTOR3D_H_

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
 * @brief This is the Vector3D class that stores both the velocity and position.
 *
 * This class has the (x,y,z) three dimensions. It is used in the Drone, Customer, and Package classes.
 */

  class Vector3D
  {
  public:
    /**
   * @brief Constructor: set up a Vector3D with a specified velocity and position
   */
    Vector3D(std::vector<float>& vector3d);

    /**
   *  This function returns the vector
   */
    const std::vector<float>& GetVector();

    /**
   *  This function sets the vector to a new vector
   */
    void SetVector(std::vector<float>& newVector);

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

#endif // VECTOR3D_H_

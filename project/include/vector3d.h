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
   * @param vector3d the three element vector that contains the values
   */
    Vector3D(std::vector<float>& vector3d);

    /**
   *  This function returns the vector
   */
    const std::vector<float>& GetVector();

    /**
   *  This function sets the vector to a new vector
   * @param newVector the new vector
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
   * @param oneVector vector number one
   * @param secondVector vector number two
   */
    std::vector<float> AddTwoVectors(std::vector<float> &oneVector, std::vector<float> &secondVector);
    /**
   *  This function should be used to subtract two standard vectors from each other
   * @param oneVector vector number one
   * @param secondVector vector number two to be subtracted from vector number one
   */
    std::vector<float> SubtractTwoVectors(std::vector<float> &oneVector, std::vector<float> &secondVector);
    /**
   *  This function should be used to multiple a vector with a float
   * @param oneVector vector number one
   * @param coeff the coefficient to multiply the vector by
   */
    std::vector<float> MultiplyVectorWithFloat(std::vector<float> &oneVector, float coeff);

  private:
    std::vector<float> vector_;
  };

} // namespace csci3081

#endif // VECTOR3D_H_

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
    Vector3D(std::vector<float> position, std::vector<float> velocity);

  /**
   *  This function returns the normalized version of the velocity (which is equivalent to the direction)
   */
    const std::vector<float> GetUnitVector();

  /**
   *  This function calculates the magnitude of the velocity (which is equivalent to the speed)
   */
    float CalculateMagnitude();

  /**
   *  This function should return the velocity component of the Vector3D
   */
    const std::vector<float>& GetVelocity();

  /**
   *  This function should return the position component of the Vector3D
   */
    const std::vector<float>& GetPosition();

    /**
   *  This function should return the direction of the package, which is the normalized velocity vector
   */
    const std::vector<float> &GetDirection();
    /**
   *  This function should set the velocity component of the Vector3D
   */
    void SetVelocity(std::vector<float> newVelocity);
    /**
   *  This function should set the position component of the Vector3D
   */
    void SetPosition(std::vector<float> newPosition);
    /**
   *  This function should be used to add two standard vectors with each other
   */
    std::vector<float> AddTwoVectors(std::vector<float>& oneVector, std::vector<float>& secondVector);
    /**
   *  This function should be used to subtract two standard vectors from each other
   */
    std::vector<float> SubtractTwoVectors(std::vector<float> &oneVector, std::vector<float> &secondVector);
    /**
   *  This function should be used to multiple a vector with a float
   */
    std::vector<float> MultiplyVectorWithFloat(std::vector<float> &oneVector, float coeff);

  private:
    std::vector<float> velocity_;
    std::vector<float> position_;
    std::vector<float> direction_;
  };

} // namespace csci3081

#endif // VECTOR3D_H_

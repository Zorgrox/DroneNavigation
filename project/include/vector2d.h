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
   * @brief Constructor: set up a Vector2D with a default constructor
   */
    Vector2D();
    /**
   * @brief Constructor: set up a Vector2D with a specified velocity and position
   */
    Vector2D(std::vector<float> position, std::vector<float> velocity);

    /**
   *  This function returns the normalized version of the velocity (which is equivalent to the direction)
   */
    const std::vector<float> GetUnitVector();

    /**
   *  This function calculates the magnitude of the velocity (which is equivalent to the speed)
   */
    float CalculateMagnitude();

    /**
   *  This function should return the velocity of the package
   */
    const std::vector<float>& GetVelocity() const;

    /**
   *  This function should return the position of the package
   */
    const std::vector<float>& GetPosition() const;
    /**
   *  This function should return the direction of the package, which is the normalized velocity vector
   */
    const std::vector<float>& GetDirection();
    /**
   *  This function should set the velocity component of the Vector3D
   */
    void SetVelocity(std::vector<float> newVelocity);
    /**
   *  This function should set the position component of the Vector3D
   */
    void SetPosition(std::vector<float> newPosition);

  private:
    std::vector<float> velocity_;
    std::vector<float> position_;
    std::vector<float> direction_;
  };

} // namespace csci3081

#endif // VECTOR2D_H_

/**
 *@file robot_factory.h
 */
#ifndef ROBOT_FACTORY_H
#define ROBOT_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/entity_factory.h>
#include "robot.h"

#include <iostream>

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief The robot factory is used to create package entities.
 * See the documentation for IEntityFactory for more information
 */
  class RobotFactory : public IEntityFactory
  {
  public:
    /**
   *  @brief Constructor: set up the robot factory
   */
    RobotFactory() {}
    /**
   *  This function creates a new robot.
   * @param val the picojson object that holds the details of the entity
   */
    IEntity *CreateEntity(const picojson::object &val) {
      std::cout << "The robot factory has been called" << std::endl;
      return new Robot(val);
    }
  };

} // namespace csci3081

#endif // ROBOT_FACTORY_H

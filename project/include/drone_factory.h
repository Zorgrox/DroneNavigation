/**
 *@file drone_factory.h
 */
#ifndef DRONE_FACTORY_H
#define DRONE_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/entity_factory.h>
#include "drone.h"

#include <iostream>

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief The drone factory is used to create package entities.
 * See the documentation for IEntityFactory for more information
 */
  class DroneFactory : public IEntityFactory
  {
  public:
    /**
   *  @brief Constructor: set up the drone factory
   */
    DroneFactory() {}
    /**
   *  This function creates a new drone.
   * @param val picojson object with details for the creation of the entity
   */
    IEntity *CreateEntity(const picojson::object &val) {
      std::cout << "The drone factory has been called" << std::endl;
      return new Drone(val);
    }
  };

} // namespace csci3081

#endif // DRONE_FACTORY_H

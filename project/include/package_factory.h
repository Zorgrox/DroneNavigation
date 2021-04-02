/**
 *@file package_factory.h
 */
#ifndef PACKAGE_FACTORY_H
#define PACKAGE_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/entity_factory.h>
#include "package.h"

#include <iostream>

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief The package factory is used to create package entities.
 *
 * See the documentation for IEntityFactory for more information
 */
  class PackageFactory : public IEntityFactory
  {
  public:
    /**
   *  @brief Constructor: set up the package factory
   */
    PackageFactory() {}
    /**
   *  This function creates a new package
   */
    IEntity *CreateEntity(const picojson::object &val) {
      std::cout << "The package factory has been called" << std::endl;
      return new Package(val);
    }
  };

} // namespace csci3081

#endif // PACKAGE_FACTORY_H

/**
 *@file customer_factory.h
 */
#ifndef CUSTOMER_FACTORY_H
#define CUSTOMER_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/entity_factory.h>
#include "customer.h"

#include <iostream>

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief The customer factory is used to create customer entities.
 * See the documentation for IEntityFactory for more information
 */
  class CustomerFactory : public IEntityFactory
  {
  public:
    /**
   *  @brief Constructor: set up the customer factory
   */
    CustomerFactory() {}
    /**
   *  This function creates a new customer
   * @param val picojson object with details for the creation of the entity
   */
    IEntity *CreateEntity(const picojson::object &val) {
      std::cout << "The customer factory has been called" << std::endl;
      return new Customer(val);
    }
  };

} // namespace csci3081

#endif // CUSTOMER_FACTORY_H

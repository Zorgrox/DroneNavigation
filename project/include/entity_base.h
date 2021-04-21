/**
 *@file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating entities.
 *
 * This class can be used as the base for all entities in the delivery system.
 * The overall design is up to you (the student), but all entities must implement
 * the IEntity interface.
 *
 * See the documentation for IEntity for more information
 */
class EntityBase : public IEntity {
 public:

  virtual ~EntityBase() {}
  /**
   *  This function should return the details of the JSON object that specifies the details of the entity
   */
  const picojson::object& GetDetails() { return details_; }
  /**
   *  This function sets the ID of the entity
   */
  void virtual SetId(int ID) {id = ID;}

 protected:
  picojson::object details_;
  int id = 0;
};

}  // namespace csci3081


#endif  // ENTITY_BASE_H_

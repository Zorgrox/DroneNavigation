/**
 * @file decorated_entity.h
 */
#ifndef DECORATED_ENTITY_H_
#define DECORATED_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "drone.h"
#include "entity_base.h"
#include "robot.h"
#include "json_helper.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the decorated entity class that is used to pick up packages and deliver them to customers. It will change color based on battery life.
 *
 * This class manages the entity's details and controls its movement.
 */

  class DecoratedEntity : public csci3081::EntityBase
  {
  public:
    /**
   * @brief Constructor: set up a decorated IEntity according to the details in the JSON object
   * @param original EntityBase object with details for the creation of the entity
   */
    DecoratedEntity( EntityBase* original);

    /**
   * @brief decorate and call the update function of the decorated entity object
   * @param IGraph needed for the smart route nodes
   * @param IEntityObservers to update the scene
   * @param float dt as the change in time between updates
   */
    void Update(const IGraph *graph, std::vector<IEntityObserver *> &observers, float dt);

    /**
   * Gets the Id of the decorated entity
   */
    int GetId() const;

    /**
   * Gets the name of the decorated entity
   */
    const std::string &GetName();

    /**
   * Gets the position of the decorated entity
   */
    const std::vector<float>& GetPosition() const;

    /**
   * Gets the direction of the decorated entity
   */
    const std::vector<float>& GetDirection() const;

    /**
   * Gets the radius of the decorated entity
   */
    float GetRadius() const;

    /**
   * Gets the version of the decorated entity
   */
    int GetVersion() const;

    /**
   * Checks whether the decorated entity is dynamic
   */
    bool IsDynamic() const;

  private:
    EntityBase* decorated_entity;
  };

}

#endif

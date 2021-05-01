/**
 * @file drone.h
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
 * @brief This is the decorated drone class that is used to pick up packages and deliver them to customers. It will change color based on battery life.
 *
 * This class manages the drone's details and controls its movement.
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
    
    int GetId() const;
    
    const std::string &GetName();
    
    const std::vector<float>& GetPosition() const;
    
    const std::vector<float>& GetDirection() const;
    
    float GetRadius() const;
    
    int GetVersion() const;
    
    bool IsDynamic() const;
    
  private:
    EntityBase* decorated_entity;
  };

}

#endif

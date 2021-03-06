/**
 * @file delivery_simulation.h
 */
#ifndef DELIVERY_SIMULATION_H_
#define DELIVERY_SIMULATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>
#include "composite_factory.h"
#include "customer.h"
#include "package.h"
#include "drone.h"
#include "robot.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the facade for the delivery system
 *
 * This class will delegate operations for the whole drone delivery system.
 * See the documentation for IDeliverySystem for more information.
 */

// DO NOT MODIFY (unless you really know what you are doing)
class DeliverySimulation : public IDeliverySystem {
 public:
  /**
   * @brief Constructor: this can do any setup your system necessitates.
   */
  DeliverySimulation();

  /// Desconstructor: This should free any memory that your program uses.
  ~DeliverySimulation();

  /**
  Given the picojson::object val, this should create an entity.
  Based on the type of entity, there may be different fields.
  You can see the vals that will be passed in the project/web/scenes
    directory. Some of the fields are for our backend system and you don't
    need to worry about them. (for instance, mesh, rotation, offset, etc.)

  Some fields in val that you will need to create the entity correctly:

    type: string (could be "drone/customer/package")

    name: string

    position: array (contains [x_position, y_position, z_position])

    direction: array (contains [x, y, z])

    speed: float

    battery_capacity: float

  Don't add the entity to the simulation until it is passed in via AddEntity
  @param val picojson object with details for the creation of the entity
  */
  IEntity* CreateEntity(const picojson::object& val);

  /**
   *  This function should add a factory to the composite factory pattern
   * @param factory the factory for creating the entities
   */
  void AddFactory(IEntityFactory* factory);

  /**
   *  This function should add an entity to the simulation
   * @param entity the entity to be added
   */
  void AddEntity(IEntity* entity);

  /**
  This function should simply store a reference to the IGraph* somewhere.
  The IGraph contains useful functions such as the GetPath function which can
  be used to get a path from one position to another.
  @param graph the graph
  */
  void SetGraph(const IGraph* graph);

  /**
  This function tells the simulation that the IEntity* package should be delivered
  to the IEntity* dest (which is likely a customer). How the delivery takes place
  is entirely dependent on how you design your code, but it should involve a drone
  navigating to the package, picking it up, and then moving to the customer and
  dropping the package.
  @param package the package to be scheduled
  @param dest the destination of the package to be scheduled (usually the customer)
  */
  void ScheduleDelivery(IEntity* package, IEntity* dest);

  /** Adds the observer to the delivery simulation
   * @param observer the observer to be added
  */
  void AddObserver(IEntityObserver* observer);

  /** Remove the observer to the delivery simulation
   * @param observer the observer to be removed
  */
  void RemoveObserver(IEntityObserver* observer);

  /**
  GetEntities should return all entities that have been ADDED to the system
  */
  const std::vector<IEntity*>& GetEntities() const;

  /**
  This function is used to advance time in the simulation. float dt refers to the
  amount of time the update call should advance the simulation by. For instance if a drone
  moves 1 unit of distance per unit of time, and Update is called with dt=.05, then the
  drone should move 1 * .05 = .05 units of distance.

  Some things that should happen in the Update function: move drones, check if
  packages have been delivered to customers, etc.
  @param dt the amount of time the update call should advance the simulation by
  */

  void Update(float dt);

  /**
   *  This function should be used to print out the values of a vector
   * @param vectorOutput the vector that we want pretty printed
   */

  void Print(std::vector<float> &vectorOutput);

  /**
   *  This function should be used to print out the values of the path
   * @param vectorOutput the vector of vectors that we want pretty printed
   */

  void PrintPath(std::vector<std::vector<float>> &vectorOutput);

  /**
   * @brief You do not need to worry about this function
   *
   * This function takes care of turning json into function calls of your system.
   * YOU DO NOT NEED TO IMPLEMENT THIS
   *it is already implemented in the delivery_simulation.cc we have provided.
   */
  void RunScript(const picojson::array& script, IEntitySystem* system) const;

 private:
  std::vector<IEntity*> entities_;
  std::vector<Drone*> drones_;
  std::vector<Robot*> robots_;
  std::vector<Customer*> customers_;
  std::vector<Package*> packages_;
  CompositeFactory* compositeFactory_;
  const IGraph* systemGraph;

  int dronesIndex;
  int robotsIndex;
  bool assignPackageToDrone = false;

  std::vector<std::vector<float>> curRoute;
  int curRouteNextIndex;
  int curRouteLength;
  std::vector<IEntityObserver*> observers_;
  int DelivIDs = 0;

  std::vector<Drone*> dead_drones_with_remaining_packages_;
  std::vector<Robot*> dead_robots_with_remaining_packages_;
  std::vector<Package*> packages_to_be_scheduled_;
  std::vector<int> dead_drones_indices;
  std::vector<int> dead_robots_indices;

};

}  // namespace csci3081


#endif  // DELIVERY_SIMULATION_H_

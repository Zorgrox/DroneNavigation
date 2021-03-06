/**
 * @file drone.h
 */
#ifndef DRONE_H_
#define DRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "package.h"
#include "battery.h"
#include "flight_behavior.h"
#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the drone class that is used to pick up packages and deliver them to customers.
 *
 * This class manages the drone's details and controls its movement.
 */

  class Drone : public csci3081::EntityBase
  {
  public:
    /**
   * @brief Constructor: set up a Drone according to the details in the JSON object
   * @param obj picojson object with details for the creation of the entity
   */
    Drone(const picojson::object &obj);

    /**
   *  Destructor: drone
   */
    ~Drone();

  /**
   *  This function should return the id of the drone
   */
    int GetId() const;

    /**
   *  This function should update the existing graph path
   * @param newGraph the graph
   */
    void AddGraphPath(const IGraph* newGraph);

    /**
   *  This function should set the id of the drone
   * @param ID the new id
   */
    void SetId(int ID);

    /**
   *  This function return the name of the drone
   */
    const std::string &GetName();

    /**
   *  This function return the pointer to the battery of the drone
   */
    const Battery* GetBattery();

  /**
   *  This function should return the position of the drone
   */
    const std::vector<float> &GetPosition() const;

  /**
   *  This function should return the direction of the drone
   */
    const std::vector<float> &GetDirection() const;

    /**
   *  This function should return the speed of the drone
   */
    float GetSpeed();

    /**
   *  This function should set the direction of the drone
   * @param newDirection the new direction of the drone
   */
    void SetDirection(std::vector<float> newDirection);

    /**
   *  This function should set the position of the drone
   * @param newPosition the new position
   */
    void SetPosition(std::vector<float> newPosition);

  /**
   *  This function should return the radius of the drone
   */
    float GetRadius() const;

  /**
   *  This function should return the version of the drone
   */
    int GetVersion() const;

  /**
   *  This function should return a bool denoting whether the drone is dynamic
   */
    bool IsDynamic() const;

  /**
   *  This function should return a pointer to the current package that the drone is looking for/carrying
   */
    Package* GetCurPackage();

    /**
   *  This function should set the current package of the drone to a different package. Should only be called when we want to set the current package of the drone to another package.
   */
    void UpdateCurPackage();

    /**
   *  This function should return whether the drone is currently carrying a package
   */
    const bool GetIsCarryingPackage() const;

    /**
   *  This function should set the boolean that denotes whether drone is currently carrying a package
   * @param newIsCarryingPackage boolean denoting whether currently carrying package
   */
    void SetIsCarryingPackage(bool newIsCarryingPackage);

    /**
   *  This function should return whether the drone is on the way to pick up a package
   */
    const bool GetOnTheWayToPickUpPackage() const;

  /**
   *  This function should set whether the drone is on the way to pick up a package
   * @param newOnTheWayToPickUpPackage boolean denoting whether on the way to pickup package
   */
    void SetOnTheWayToPickUpPackage(bool newOnTheWayToPickUpPackage);

    /**
   *  This function should return whether the drone is on the way to drop off a package
   */
    const bool GetOnTheWayToDropOffPackage() const;

    /**
   *  This function should set whether the drone is on the way to drop off a package
   * @param newOnTheWayToDropOffPackage boolean denoting whether on the way to dropoff package
   */
    void SetOnTheWayToDropOffPackage(bool newOnTheWayToDropOffPackage);

    /**
   *  This function should update the battery's charge by decrementing it by the set amount
   * @param decrAmount the amount to decrement the battery charge
   */
    void UpdateBatteryCharge(float decrAmount);

  /**
    *  This function should update the drone's positions
    * @param dt the time difference between calls of the Update function
    * @param observers the list of observers to be notified
    */
    void UpdateDronePosition(float dt, std::vector<IEntityObserver *> &observers);

    /**
    *  This function should update the drone's velocity
    * @param newVelocity the new velocity
    */
    void UpdateDroneVelocity(std::vector<float> & newVelocity);

    /**
    *  This function is called in the Delivery Simulation's update function. It updates the drone's velocity and position based on the graph's path.
    * @param graph the graph
    * @param observers the observers to be notified
    * @param dt the time difference between calls of the Update function
    */
    void Update(const IGraph *graph, std::vector<IEntityObserver *> &observers, float dt);

    /**
    *  This function should check whether the package is ready to be picked up, within the radius
    */
    bool CheckReadyToPickUp();

    /**
    *  This function should check whether the package is ready to be dropped off, within the radius
    */
    bool CheckReadyToDropOff();

    /**
    *  This function should update the curPackage so that we pick up a new package and set the status of the drone to dropping off the package
    */
    void PickUpPackage();

    /**
    *  This function should remove the curPackage from the simulation by setting it to a ridiculous coordinate, and set the status of the drone to neither picking up nor dropping off a package
    */
    void DropOffPackage();

    /**
    *  This function should calculate the direction from the curPosition to the next node in the graph and update the drone's direction accordingly
    * @param nextPosition the next position
    */
    void CalculateAndUpdateDroneDirection(std::vector<float>& nextPosition);

    /**
    *  This function should add another Package pointer to the vector of assigned packages
    * @param newPackage the new package to be added to the list of assigned packages
    */
    void AddAssignedPackage(Package& newPackage);

    /**
    *  This function returns the number of packages in the assignedPackages vector
    */
    int GetNumAssignedPackages();

    /**
    *  This function updates the curRoute of this drone
    * @param newCurRoute the new route to be set
    */
    void SetNewCurRoute(std::vector<std::vector<float>>& newCurRoute);

    /**
    *  This function gets the length of the curRoute that the drone is following
    */
    int GetCurRouteLength();

    /**
    *  This function gets the index of the next stop within the curRoute
    */
    int GetCurRouteNextIndex();

    /**
    *  This function increments the index of the next stop within the curRoute
    */
    void IncrementCurRouteNextIndex();

    /**
    *  This function sets the flight behavior for the drone
    * @param pos the position
    * @param target the target destination
    * @param newGraph the graph
    */
    void SetFlightBehavior(std::vector<float> pos, std::vector<float> target, const IGraph* newGraph);

    /**
    *  This function chooses the flight strategy for the drone
    */
    void ChooseFlightStrategy();

    /**
    *  This function returns the list of remaining packages to be delivered by the drone, if there are any. This should only be used when checking for packages to be rescheduled in the case that the drone dies.
    */
    std::vector<Package*> GetRemainingAssignedPackages();

    /**
    *  This function sets the flight strategy index
    * @param index the index of the flight strategy
    * @param allowChange boolean denoting whether we should allow the flight strategy to be changed
    */
    void SetFlightStrategyIndex(int index, bool allowChange);

  private:
    int id;
    std::string name;
    Vector3D *position;
    Vector3D *direction;
    Package *curPackage;
    std::vector<Package *> assignedPackages;
    int assignedPackageIndex;
    Battery *battery;
    float radius;
    int version = 0;
    bool dynamic = true;
    bool onTheWayToPickUpPackage;
    bool onTheWayToDropOffPackage;
    bool isCarryingPackage;

	  bool notified = false;
    float speed;
	  int waiter=0;
	  bool allowFlightChange=true;
    std::vector<std::vector<float>> curRoute;
    int curRouteNextIndex;
    int curRouteLength;
    FlightBehavior* flightStrategy;
    int flightStrategyIndex = 0;

    float battery_capacity;

  };

} // namespace csci3081

#endif // DRONE_H_

/**
 * @file robot.h
 */
#ifndef ROBOT_H_
#define ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector2d.h"
#include "package.h"
#include "battery.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the robot class that is used to pick up packages and deliver them to customers.
 *
 * This class manages the robot's details and controls its movement.
 */

  class Robot : public csci3081::EntityBase
  {
  public:
    /**
   * @brief Constructor: set up a Robot according to the details in the JSON object
   * @param obj the picojson object that contains the details
   */
    Robot(const picojson::object &obj);

    /**
   *  Destructor: robot
   */
    ~Robot();

  /**
   *  This function should return the id of the robot
   */
    int GetId() const;

    /**
   *  This function should set the id of the robot
   * @param ID the id
   */
    void SetId(int ID);

    /**
   *  This function return the name of the robot
   */
    const std::string &GetName();

    /**
   *  This function return the pointer to the battery of the robot
   */
    const Battery* GetBattery();

    /**
   *  This function should return the position of the robot
   */
    const std::vector<float> &GetPosition() const;

  /**
   *  This function should return the direction of the robot
   */
    const std::vector<float> &GetDirection() const;

  /**
   *  This function should return the radius of the robot
   */
    float GetRadius() const;

  /**
   *  This function should return the version of the robot
   */
    int GetVersion() const;

  /**
   *  This function should return a bool denoting whether the robot is dynamic
   */
    bool IsDynamic() const;

  /**
   *  This function should return a pointer to the current package that the robot is looking for/carrying
   */
    const Package* GetCurPackage();

    /**
   *  This function should set the current package of the robot to a different package
   */
    void UpdateCurPackage();

    /**
   *  This function should return whether the robot is currently carrying a package
   */
    const bool GetIsCarryingPackage() const;

    /**
   *  This function should set the boolean that denotes whether robot is currently carrying a package
   * @param newIsCarryingPackage boolean that denotes whether robot is currently carrying a package
   */
    void SetIsCarryingPackage(bool newIsCarryingPackage);

    /**
   *  This function should return whether the robot is on the way to pick up a package
   */
    const bool GetOnTheWayToPickUpPackage() const;

    /**
   *  This function should set whether the robot is on the way to pick up a package
   * @param newOnTheWayToPickUpPackage boolean that denotes whether the robot is on the way to pick up a package
   */
    void SetOnTheWayToPickUpPackage(bool newOnTheWayToPickUpPackage);

    /**
   *  This function should return whether the robot is on the way to drop off a package
   */
    const bool GetOnTheWayToDropOffPackage() const;

    /**
   *  This function should set whether the robot is on the way to drop off a package
   * @param newOnTheWayToDropOffPackage boolean that denotes whether the robot is on the way to drop off a package
   */
    void SetOnTheWayToDropOffPackage(bool newOnTheWayToDropOffPackage);

    /**
   *  This function should update the battery's charge by decrementing it by the set amount
   * @param decrAmount the amount that the battery should be decremented by
   */
    void UpdateBatteryCharge(float decrAmount);

  /**
    *  This function should update the robot's positions
    * @param dt the time difference in calls to Update function
    * @param observers the list of observers to be notified
    */
    void UpdateRobotPosition(float dt, std::vector<IEntityObserver *> &observers);

    /**
    *  This function should update the robot's velocity
    * @param newVelocity the velocity
    */
    void UpdateRobotVelocity(std::vector<float> & newVelocity);

    /**
    *  This function is called in the Delivery Simulation's update function. It updates the robot's velocity and position based on the graph's path.
    * @param graph the graph
    * @param observers the list of observers
    * @param dt the time difference in calls to the Update function
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
    *  This function should check whether the robot should be aiming for the next node in the path
    * @param nextPosition the next position
    */
    bool CheckWhenToIncrementPathIndex(std::vector<float> &nextPosition);

    /**
    *  This function should update the curPackage so that we pick up a new package and set the status of the robot to dropping off the package
    */
    void PickUpPackage();

    /**
    *  This function should remove the curPackage from the simulation by setting it to a ridiculous coordinate, and set the status of the robot to neither picking up nor dropping off a package
    */
    void DropOffPackage();

    /**
    *  This function should calculate the direction from the curPosition to the next node in the graph and update the robot's direction accordingly
    * @param nextPosition the next position
    */
    void CalculateAndUpdateRobotDirection(std::vector<float>& nextPosition);

    /**
    *  This function should add another Package pointer to the vector of assigned packages
    * @param newPackage the new package to be added to the assigned packages list
    */
    void AddAssignedPackage(Package &newPackage);

    /**
    *  This function returns the number of packages in the assignedPackages vector
    */
    int GetNumAssignedPackages();

    /**
    *  This function updates the curRoute of this robot
    * @param newCurRoute the new route to be set
    */
    void SetNewCurRoute(std::vector<std::vector<float>> &newCurRoute);

    /**
    *  This function gets the length of the curRoute that the robot is following
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
    *  This function returns the list of remaining packages to be delivered by the robot, if there are any. This should only be used when checking for packages to be rescheduled in the case that the robot dies.
    */
    std::vector<Package *> GetRemainingAssignedPackages();

  private:
    std::string name;
    Vector2D *position;
    Vector2D *direction;
    Package *curPackage;
    std::vector<Package *> assignedPackages;
    int assignedPackageIndex;
    Battery *battery;
    float radius;
    int version = 0;
    bool dynamic = true;
	  bool notified = false;
    bool onTheWayToPickUpPackage;
    bool onTheWayToDropOffPackage;
    bool isCarryingPackage;
    float speed;
	  int waiter=0;
    std::vector<std::vector<float>> curRoute;
    int curRouteNextIndex;
    int curRouteLength;
    float battery_capacity;

  };

} // namespace csci3081

#endif // ROBOT_H_

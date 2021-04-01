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
   */
    Robot(const picojson::object &obj);

  /**
   *  This function should return the id of the robot
   */
    int GetId() const;

    /**
   *  This function should set the id of the robot
   */
    void SetId(int ID);

    /**
   *  This function return the name of the robot
   */
    const std::string &GetName();

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
   */
    void SetIsCarryingPackage(bool newIsCarryingPackage);

    /**
   *  This function should return whether the robot is on the way to pick up a package
   */
    const bool GetOnTheWayToPickUpPackage() const;

  /**
   *  This function should set whether the robot is on the way to pick up a package
   */
    void SetOnTheWayToPickUpPackage(bool newOnTheWayToPickUpPackage);

    /**
   *  This function should return whether the robot is on the way to drop off a package
   */
    const bool GetOnTheWayToDropOffPackage() const;

    /**
   *  This function should set whether the robot is on the way to drop off a package
   */
    void SetOnTheWayToDropOffPackage(bool newOnTheWayToDropOffPackage);

    /**
   *  This function should update the battery's charge by decrementing it by the set amount
   */
    void UpdateBatteryCharge(float decrAmount);

  /**
    *  This function should update the robot's positions
    */
    void UpdateRobotPosition(float dt);

  /**
    *  This function should update the robot's velocity
    */
    void UpdateRobotVelocity(std::vector<float> & newVelocity);

    /**
    *  This function is called in the Delivery Simulation's update function. It updates the robot's velocity and position based on the graph's path.
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
    */
    void CalculateAndUpdateRobotDirection(std::vector<float>& nextPosition);

    /**
    *  This function should add another Package pointer to the vector of assigned packages
    */
    void AddAssignedPackage(Package &newPackage);

    /**
    *  This function returns the number of packages in the assignedPackages vector
    */
    int GetNumAssignedPackages();

    /**
    *  This function updates the curRoute of this robot
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
    bool onTheWayToPickUpPackage;
    bool onTheWayToDropOffPackage;
    bool isCarryingPackage;
    float speed;

    std::vector<std::vector<float>> curRoute;
    int curRouteNextIndex;
    int curRouteLength;
    };

} // namespace csci3081

#endif // ROBOT_H_

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
   */
    Drone(const picojson::object &obj);

  /**
   *  This function should return the id of the drone
   */
    int GetId() const;

  /**
   *  This function return the name of the drone
   */
    const std::string &GetName();

  /**
   *  This function should return the position of the drone
   */
    const std::vector<float> &GetPosition() const;

  /**
   *  This function should return the direction of the drone
   */
    const std::vector<float> &GetDirection() const;

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
    const Package* GetCurPackage();

    /**
   *  This function should set the current package of the drone to a different package
   */
    void SetCurPackage(Package &newPackage);

    /**
   *  This function should return whether the drone is currently carrying a package
   */
    const bool GetIsCarryingPackage() const;

    /**
   *  This function should set the boolean that denotes whether drone is currently carrying a package
   */
    void SetIsCarryingPackage(bool newIsCarryingPackage);

    /**
   *  This function should return whether the drone is on the way to pick up a package
   */
    const bool GetOnTheWayToPickUpPackage() const;

  /**
   *  This function should set whether the drone is on the way to pick up a package
   */
    void SetOnTheWayToPickUpPackage(bool newOnTheWayToPickUpPackage);

    /**
   *  This function should return whether the drone is on the way to drop off a package
   */
    const bool GetOnTheWayToDropOffPackage() const;

    /**
   *  This function should set whether the drone is on the way to drop off a package
   */
    void SetOnTheWayToDropOffPackage(bool newOnTheWayToDropOffPackage);

    /**
   *  This function should update the battery's charge by decrementing it by the set amount
   */
    void UpdateBatteryCharge(float decrAmount);

  /**
    *  This function should update the drone's positions
    */
    void UpdateDronePosition(std::vector<float> & newPosition);

  /**
    *  This function should update the drone's velocity
    */
    void UpdateDroneVelocity(std::vector<float> & newVelocity);

    /**
    *  This function is called in the Delivery Simulation's update function. It updates the drone's velocity and position based on the graph's path.
    */
    void Update(float dt);

    /**
    *  This function should check whether the package is ready to be picked up, within the radius
    */
    bool CheckReadyToPickUp();

    /**
    *  This function should check whether the package is ready to be dropped off, within the radius
    */
    bool CheckReadyToDropOff();

    /**
    *  This function should check whether the drone should be aiming for the next node in the path
    */
    bool CheckWhenToIncrementPathIndex(std::vector<float> &nextPosition);

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
    */
    void CalculateAndUpdateDroneDirection(std::vector<float>& nextPosition);

    private:
      int id;
      std::string name;
      Vector3D* position;
      Vector3D* direction;
      Package *curPackage;
      Battery *battery;
      float radius;
      int version = 0;
      bool dynamic = true;
      bool onTheWayToPickUpPackage;
      bool onTheWayToDropOffPackage;
      bool isCarryingPackage;
      float speed;
    };

} // namespace csci3081

#endif // DRONE_H_

#include "robot.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector2d.h"
#include "package.h"
#include "battery.h"
#include "json_helper.h"

#include <iostream>
#include <cmath>

#include <EntityProject/graph.h>

namespace csci3081 {

  Robot::Robot(const picojson::object &obj)
  {
    name = JsonHelper::GetString(obj, "name");
    std::vector<float> positionVec = JsonHelper::GetStdFloatVector(obj, "position");
    std::vector<float> directionVec = JsonHelper::GetStdFloatVector(obj, "direction");
    position = new Vector2D(positionVec);
    direction = new Vector2D(directionVec);
    direction->Normalize();
    radius = (float) JsonHelper::GetDouble(obj, "radius");
    onTheWayToPickUpPackage = false;
    onTheWayToDropOffPackage = false;
    isCarryingPackage = false;
    try
    {
      battery_capacity = JsonHelper::GetDouble(obj, "battery_capacity");
    }
    catch (const std::logic_error)
    {
      battery_capacity = 10000;
    }
    battery = new Battery(battery_capacity);
    speed = (float) JsonHelper::GetDouble(obj, "speed");
    details_ = obj;
    assignedPackageIndex = 0;
    // curPackage = new Package();
    std::cout << "Creating robot in default constructor" << std::endl;
    std::cout << "This is Robot's current position in default constructor: {" << positionVec.at(0) << ", " << positionVec.at(1) << ", " << positionVec.at(2) << "}" << std::endl;
    std::cout << "This is Robot's current direction in default constructor: {" << directionVec.at(0) << ", " << directionVec.at(1) << ", " << directionVec.at(2) << "}" << std::endl;
  }

  int Robot::GetId() const {
    return id;
  }

  void Robot::SetId(int ID) {
	  id = ID;
  }

  const std::string& Robot::GetName() {
    return name;
  }

  const Battery *Robot::GetBattery() {
    return battery;
  }

  const std::vector<float>& Robot::GetPosition() const {
    return position->GetVector();
  }

  const std::vector<float>& Robot::GetDirection() const {
    return direction->GetVector();
  }

  float Robot::GetRadius() const
  {
    return radius;
  }

  int Robot::GetVersion() const
  {
    return version;
  }

  bool Robot::IsDynamic() const
  {
    return dynamic;
  }

  const Package* Robot::GetCurPackage() {
    return curPackage;
  }

  void Robot::UpdateCurPackage()
  {
    if (assignedPackageIndex < GetNumAssignedPackages())
    {
      curPackage = assignedPackages.at(assignedPackageIndex);
    }
    // curPackage = &newPackage;
  }

  void Robot::AddAssignedPackage(Package &newPackage)
  {
    assignedPackages.push_back(&newPackage);
  }

  const bool Robot::GetIsCarryingPackage() const {
    return isCarryingPackage;
  }

  void Robot::SetIsCarryingPackage(bool newIsCarryingPackage) {
    isCarryingPackage = newIsCarryingPackage;
  }

  const bool Robot::GetOnTheWayToPickUpPackage() const {
    return onTheWayToPickUpPackage;
  }

  void Robot::SetOnTheWayToPickUpPackage(bool newOnTheWayToPickUpPackage) {
    onTheWayToPickUpPackage = newOnTheWayToPickUpPackage;
  }

  const bool Robot::GetOnTheWayToDropOffPackage() const {
    return onTheWayToDropOffPackage;
  }

  void Robot::SetOnTheWayToDropOffPackage(bool newOnTheWayToDropOffPackage) {
    onTheWayToDropOffPackage = newOnTheWayToDropOffPackage;
  }

  void Robot::UpdateBatteryCharge(float decrAmount) {
    battery->DecrementCurrentCharge(decrAmount);
  }

  void Robot::UpdateRobotPosition(float dt, std::vector<IEntityObserver *> &observers)
  {
    std::vector<float> directionVec = GetDirection();
    std::vector<float> curPosition = GetPosition();

    float speedAndDt = speed * dt;

    std::vector<float> updateDirection = direction->MultiplyVectorWithFloat(directionVec, speedAndDt);
    std::vector<float> newPosition = position->AddTwoVectors(curPosition, updateDirection);

    // std::cout << "This is Drone new position: {" << newPosition.at(0) << ", " << newPosition.at(1) << ", " << newPosition.at(2) << "}" << std::endl;

    if (battery->GetIsEmpty() == false)
    {
      position->SetVector(newPosition);

      if (isCarryingPackage)
      {
        // then also update the package's position
        curPackage->SetPosition(newPosition);
      }
      if (onTheWayToDropOffPackage || onTheWayToPickUpPackage)
      {
        UpdateBatteryCharge(dt);
      }
    }
    if (battery->GetIsEmpty() == true)
    {
      // The battery is now empty (after moving in the condition above)! So we have to announce that the drone / robot is in idle, since it's out of battery picojson::object obj3 = JsonHelper::CreateJsonObject();
      picojson::object obj3 = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(obj3, "type", "notify");
      JsonHelper::AddStringToJsonObject(obj3, "value", "idle");
      JsonHelper::AddStdVectorVectorFloatToJsonObject(obj3, "path", curRoute);
      picojson::value val3 = JsonHelper::ConvertPicojsonObjectToValue(obj3);
      for (IEntityObserver *obs : observers)
      {
        const IEntity *temp_drone = this;
        obs->OnEvent(val3, *temp_drone);
      }
      if (isCarryingPackage)
      {
        SetIsCarryingPackage(false);
      }
      // also set the on the way to drop off package and pick up package to false
      onTheWayToDropOffPackage = false;
      onTheWayToPickUpPackage = false;
    }
    std::cout << "This is battery charge of ROBOT: " << battery->GetCurrentCharge() << std::endl;
  }

  void Robot::UpdateRobotVelocity(std::vector<float> &newVelocity) {
    direction->SetVector(newVelocity);
    direction->Normalize();
    if (isCarryingPackage) {
      // then also update the package's velocity
      curPackage->SetVelocity(newVelocity);
    }
  }

  void Robot::Update(const IGraph *graph, std::vector<IEntityObserver *> &observers, float dt)
  {
    std::cout << "These print statements are for Robot name " << name << std::endl;
    std::cout << "===================================" << std::endl;
    if (battery->GetIsEmpty() == false) {
      if (GetOnTheWayToPickUpPackage() && !GetOnTheWayToDropOffPackage())
      {
        ///////////////// Checks to see if the route is there or not
        if(!notified) // Checks to see if its announced that its on its way to the package
        {
          if (waiter==30) { //Presumably due to threading of some sort, we need to wait for currRoute to actually be there
            picojson::object obj2 = JsonHelper::CreateJsonObject();
            JsonHelper::AddStringToJsonObject(obj2, "type", "notify");
            JsonHelper::AddStringToJsonObject(obj2, "value", "moving");
            JsonHelper::AddStdVectorVectorFloatToJsonObject(obj2, "path", curRoute);
            picojson::value val2 = JsonHelper::ConvertPicojsonObjectToValue(obj2);
            for (IEntityObserver *obs : observers)
            {
              const IEntity *temp_robot = this;
              obs->OnEvent(val2, *temp_robot);
            }
            notified=true;
          }
          else
          {
            waiter++;
          }
        }

        ////////////////
        std::cout << "I'm on the way to pick up the package" << std::endl;
        // The drone is on the way to pick up a package.
        if (CheckReadyToPickUp())
        {
          std::cout << "Ready to pickup\n";
          PickUpPackage();
          // Update the path so that it's now pointed towards the customer's location

          std::vector<std::vector<float>> anotherRoute = graph->GetPath(GetPosition(), GetCurPackage()->GetDestination());
          SetNewCurRoute(anotherRoute);
          std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
          CalculateAndUpdateRobotDirection(nextPos);
          std::cout << "This is Robot's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
          SetOnTheWayToPickUpPackage(false);
          SetOnTheWayToDropOffPackage(true);
          curRouteNextIndex = 1;
          std::cout << "Switching over to dropping package off" << std::endl;

          // Notify the observers that the package has been picked up
          picojson::object obj = JsonHelper::CreateJsonObject();
          JsonHelper::AddStringToJsonObject(obj, "type", "notify");
          JsonHelper::AddStringToJsonObject(obj, "value", "en route");
          picojson::value val = JsonHelper::ConvertPicojsonObjectToValue(obj);

          for (IEntityObserver *obs : observers)
          {
            const IEntity *temp_pkg = GetCurPackage();
            obs->OnEvent(val, *temp_pkg);
          }
          /////////////// Notify that the robot is moving when picked up package
          picojson::object obji = JsonHelper::CreateJsonObject();
          JsonHelper::AddStringToJsonObject(obji, "type", "notify");
          JsonHelper::AddStringToJsonObject(obji, "value", "moving");
          JsonHelper::AddStdVectorVectorFloatToJsonObject(obji, "path", curRoute);
          picojson::value vali = JsonHelper::ConvertPicojsonObjectToValue(obji);
          for (IEntityObserver *obs : observers)
          {
            const IEntity *temp_robot = this;
            obs->OnEvent(vali, *temp_robot);
          }

        }
        else
        {
          if (CheckWhenToIncrementPathIndex(curRoute.at(curRouteNextIndex)))
          {
            // We should only increment the path index when the drone gets close enough to it that we should be going to the next one
            std::cout << "I'M JUST INCREMENTING THE PATH INDEX ON THE WAY TO PICK UP THE PACKAGE" << std::endl;
            curRouteNextIndex = curRouteNextIndex + 1;
            std::vector<float> nextPos;
            if (curRouteNextIndex >= curRoute.size()){
              nextPos = curPackage->GetPosition();
              curRouteNextIndex = curRouteNextIndex - 1;
            } else {
              nextPos = curRoute.at(curRouteNextIndex);}
              std::cout << "This is Robot's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
              CalculateAndUpdateRobotDirection(nextPos);
          }
          else
          {
            // We don't need to increment the path index yet
            std::cout << "Don't need to increment path index yet" << std::endl;
            std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
            std::cout << "This is Robot's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
            CalculateAndUpdateRobotDirection(nextPos);
          }
        }
        UpdateRobotPosition(dt, observers);
      }

      else if (!GetOnTheWayToPickUpPackage() && GetOnTheWayToDropOffPackage())
      {
        std::cout << "I'm on the way to drop off the package" << std::endl;
        if (CheckReadyToDropOff())
        {
          // Move the package out of the simulation to remove it
          curRouteNextIndex = 1;
          DropOffPackage();

          // Notify the observers that the package has been delivered
          picojson::object obj = JsonHelper::CreateJsonObject();
          JsonHelper::AddStringToJsonObject(obj, "type", "notify");
          JsonHelper::AddStringToJsonObject(obj, "value", "delivered");
          picojson::value val = JsonHelper::ConvertPicojsonObjectToValue(obj);

          for (IEntityObserver *obs : observers)
          {
            const IEntity *temp_pkg = GetCurPackage();
            obs->OnEvent(val, *temp_pkg);
          }
          /////////////// Goes into idle since package dropped off.
          picojson::object obj3 = JsonHelper::CreateJsonObject();
          JsonHelper::AddStringToJsonObject(obj3, "type", "notify");
          JsonHelper::AddStringToJsonObject(obj3, "value", "idle");
          JsonHelper::AddStdVectorVectorFloatToJsonObject(obj3, "path", curRoute);
          picojson::value val3 = JsonHelper::ConvertPicojsonObjectToValue(obj3);
          for (IEntityObserver *obs : observers)
          {
            const IEntity *temp_robot = this;
            obs->OnEvent(val3, *temp_robot);
          }

          // if there's another package it has to go to, then assign this new package to the curPackage
          if (assignedPackageIndex < GetNumAssignedPackages())
          {
            std::cout << "IMPORTANT: I'm here assigning a new package to the curPackage in ROBOT" << std::endl;
            UpdateCurPackage();
            std::vector<std::vector<float>> anotherRoute = graph->GetPath(GetPosition(), curPackage->GetPosition());
            SetNewCurRoute(anotherRoute);

            SetOnTheWayToPickUpPackage(true);
            SetOnTheWayToDropOffPackage(false);
          }
        }
        else
        {
          if (CheckWhenToIncrementPathIndex(curRoute.at(curRouteNextIndex)))
          {
            curRouteNextIndex = curRouteNextIndex + 1;
            std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
            CalculateAndUpdateRobotDirection(nextPos);
          }
          else
          {
            // We don't need to increment the path index yet
            std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
            CalculateAndUpdateRobotDirection(nextPos);
          }
          UpdateRobotPosition(dt, observers);
        }
      }
    }
  }

  bool Robot::CheckReadyToPickUp()
  {
    std::vector<float> currentPosition = GetPosition();
    std::vector<float> packagePosition = curPackage->GetPosition();
    std::cout << "I am in Robot::CheckReadyToPickUp checking the curPackage's position" << std::endl;
    std::cout << "This is Robot's current position in CheckReadyToPickUp: {" << currentPosition.at(0) << ", " << currentPosition.at(1) << ", " << currentPosition.at(2) << "}" << std::endl;
    std::cout << "This is Package's current position in CheckReadyToPickUp: {" << packagePosition.at(0) << ", " << packagePosition.at(1) << ", " << packagePosition.at(2) << "}" << std::endl;
    if (std::fabs(currentPosition.at(0)-packagePosition.at(0))<=radius && std::fabs(currentPosition.at(2)-packagePosition.at(2)) <= radius)
	  {
		  return true;
	  } else {
      return false;
    }
  }

  bool Robot::CheckReadyToDropOff() {
    std::vector<float> currentPosition = GetPosition();
    std::vector<float> packageDestination = curPackage->GetDestination();
    std::vector<float> packagePosition = curPackage->GetPosition();
    int i = 0;
    int numWithinRadius = 0;
    std::cout << "This is Robot's current position in CheckReadyToDropOff: {" << currentPosition.at(0) << ", " << currentPosition.at(1) << ", " << currentPosition.at(2) << "}" << std::endl;
    std::cout << "This is Package's current position in CheckReadyToDropOff: {" << packagePosition.at(0) << ", " << packagePosition.at(1) << ", " << packagePosition.at(2) << "}" << std::endl;
    if (std::fabs(currentPosition.at(0)-packageDestination.at(0))<=radius&&std::fabs(currentPosition.at(2)-packageDestination.at(2))<=radius)
	{
		return true;
	}
    else
    {
      return false;
    }
  }

  bool Robot::CheckWhenToIncrementPathIndex(std::vector<float>& nextPosition)
  {
    std::cout << "I am checking when to increment the path index" << std::endl;

    std::vector<float> currentPosition = GetPosition();
    int i = 0;
    int numWithinRadius = 0;
    for (float pos : currentPosition)
    {
      float nextPos = nextPosition.at(i);
      i = i + 1;
      // std::cout << "This is pos: " << pos << std::endl;
      // std::cout << "This is nextPos: " << nextPos << std::endl;
      if (std::fabs(pos - nextPos) <= radius * 2.0)
      {
        numWithinRadius = numWithinRadius + 1;
      }
    }
    if (numWithinRadius == 2)
    {
      std::cout << "It is within radius to increment path index" << std::endl;
      return true;
    }
    else
    {
      std::cout << "It is NOT within radius to increment path index" << std::endl;
      return false;
    }
  }

  void Robot::PickUpPackage() {
    isCarryingPackage = true;
    onTheWayToPickUpPackage = false;
    onTheWayToDropOffPackage = true;
  }

  void Robot::DropOffPackage() {
    isCarryingPackage = false;
    std::vector<float> outOfTheWayPosition{10, 1000, 10};
    curPackage->SetPosition(outOfTheWayPosition);
    onTheWayToPickUpPackage = false;
    onTheWayToDropOffPackage = false;
	  notified=false;
	  waiter = 0;
    // also set the robot's direction to 0,0,0 so that we stop moving
    std::vector<float> stopMoving{0.0001,0.0001,0.0001};
    UpdateRobotVelocity(stopMoving);
    curPackage->SetVelocity(stopMoving);
    assignedPackageIndex = assignedPackageIndex + 1;
    std::cout << "I've dropped off the package" << std::endl;
  }

  void Robot::CalculateAndUpdateRobotDirection(std::vector<float> &nextPosition) {
    std::vector<float> currentPosition = position->GetVector();
    std::vector<float> newVelocity = position->SubtractTwoVectors(nextPosition, currentPosition);
    UpdateRobotVelocity(newVelocity);
  }

  int Robot::GetNumAssignedPackages()
  {
    return assignedPackages.size();
  }

  void Robot::SetNewCurRoute(std::vector<std::vector<float>> &newCurRoute)
  {
    // resets the curRoute
    curRoute = newCurRoute;
    curRouteLength = curRoute.size();
    curRouteNextIndex = 1;
  }

  int Robot::GetCurRouteLength()
  {
    return curRouteLength;
  }

  int Robot::GetCurRouteNextIndex()
  {
    return curRouteNextIndex;
  }

  void Robot::IncrementCurRouteNextIndex()
  {
    curRouteNextIndex = curRouteNextIndex + 1;
  }

  std::vector<Package *> Robot::GetRemainingAssignedPackages()
  {
    // first need to check whether the curpackageindex is within range of the packageslist
    // if it's not, then we just return an empty vector
    // if it is, then we return everything after that package, itself included
    std::vector<Package *> remainingAssignedPackages;
    for (int i = assignedPackageIndex; i < GetNumAssignedPackages(); i++)
    {
      remainingAssignedPackages.push_back(assignedPackages.at(i));
    }
    return remainingAssignedPackages;
  }
}

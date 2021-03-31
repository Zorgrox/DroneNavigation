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
    battery = new Battery(10000);
    speed = (float) JsonHelper::GetDouble(obj, "speed");
    details_ = obj;
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

  void Robot::SetCurPackage(Package& newPackage) {
    curPackage = &newPackage;
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


  void Robot::UpdateRobotPosition(std::vector<float> &newPosition, float dt) {

    std::cout << "This is Robot new position: {" << id << ", " << newPosition.at(1) << ", " << newPosition.at(2) << "}" << std::endl;

    if (battery->GetIsEmpty()==false) {
        position->SetVector(newPosition);

        if (isCarryingPackage) {
          // then also update the package's position
          curPackage->SetPosition(newPosition);
        }
    UpdateBatteryCharge(-dt);

    }

  }

  void Robot::UpdateRobotVelocity(std::vector<float> &newVelocity) {
    direction->SetVector(newVelocity);
    direction->Normalize();
    if (isCarryingPackage) {
      // then also update the package's velocity
      curPackage->SetVelocity(newVelocity);
    }
  }

  void Robot::Update(float dt)
  {
    std::vector<float> directionVec = GetDirection();
    std::vector<float> curPosition = GetPosition();

    float speedAndDt = speed * dt;

    std::vector<float> updateDirection = direction->MultiplyVectorWithFloat(directionVec, speedAndDt);
    std::vector<float> nextPosition =  position->AddTwoVectors(curPosition, updateDirection);
    UpdateRobotPosition(nextPosition, dt);

    // Decrement the robot's battery

    // TODO: for later iteration, give a warning if the robot's battery is close to being depleted
  }

  bool Robot::CheckReadyToPickUp()
  {
    std::vector<float> currentPosition = GetPosition();
    std::vector<float> packagePosition = curPackage->GetPosition();
    std::cout << "I am in Robot::CheckReadyToPickUp checking the curPackage's position" << std::endl;
    int i = 0;
    int numWithinRadius = 0;
    std::cout << "This is Robot's current position in CheckReadyToPickUp: {" << currentPosition.at(0) << ", " << currentPosition.at(1) << ", " << currentPosition.at(2) << "}" << std::endl;
    std::cout << "This is Package's current position in CheckReadyToPickUp: {" << packagePosition.at(0) << ", " << packagePosition.at(1) << ", " << packagePosition.at(2) << "}" << std::endl;
    for(float pos : currentPosition) {
      float packagePos = packagePosition.at(i);
      i = i + 1;
      // std::cout << "I am about to subtract the package position from the position" << std::endl;
      if (std::fabs(pos - packagePos) <= radius) {
        // std::cout << "I am in the pos - packagePos <= radius condition" << std::endl;
        numWithinRadius = numWithinRadius + 1;
      }
      // std::cout << "I am done subtracting the package position from the position" << std::endl;
    }
    if (numWithinRadius == 3) {
      std::cout << "The package is ready to be picked up!" << std::endl;
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
    for (float pos : currentPosition)
    {
      float packageDes = packageDestination.at(i);
      i = i + 1;
      if (std::fabs(pos - packageDes) <= radius)
      {
        numWithinRadius = numWithinRadius + 1;
      }
    }
    if (numWithinRadius == 3)
    {
      std::cout << "The package is ready to be dropped off!" << std::endl;
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
      if (std::fabs(pos - nextPos) <= radius)
      {
        numWithinRadius = numWithinRadius + 1;
      }
    }
    if (numWithinRadius == 3)
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
    // also set the robot's direction to 0,0,0 so that we stop moving
    std::vector<float> stopMoving{0.0001,0.0001,0.0001};
    UpdateRobotVelocity(stopMoving);
    curPackage->SetVelocity(stopMoving);
    std::cout << "I've dropped off the package" << std::endl;
  }

  void Robot::CalculateAndUpdateRobotDirection(std::vector<float> &nextPosition) {
    std::vector<float> currentPosition = position->GetVector();
    std::vector<float> newVelocity = position->SubtractTwoVectors(nextPosition, currentPosition);
    UpdateRobotVelocity(newVelocity);
  }

}

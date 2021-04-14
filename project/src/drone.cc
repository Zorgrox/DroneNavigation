#include "drone.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "package.h"
#include "battery.h"
#include "json_helper.h"

#include <iostream>
#include <cmath>

#include <EntityProject/graph.h>

namespace csci3081 {

  Drone::Drone(const picojson::object &obj)
  {
    name = JsonHelper::GetString(obj, "name");
    std::vector<float> positionVec = JsonHelper::GetStdFloatVector(obj, "position");
    std::vector<float> directionVec = JsonHelper::GetStdFloatVector(obj, "direction");
    position = new Vector3D(positionVec);
    direction = new Vector3D(directionVec);
    direction->Normalize();
    radius = (float) JsonHelper::GetDouble(obj, "radius");
    onTheWayToPickUpPackage = false;
    onTheWayToDropOffPackage = false;
    isCarryingPackage = false;
    battery = new Battery(10000);
    speed = (float) JsonHelper::GetDouble(obj, "speed");
    assignedPackageIndex = 0;
    details_ = obj;
    // curPackage = new Package();
    std::cout << "Creating drone in default constructor" << std::endl;
    std::cout << "This is Drone's current position in default constructor: {" << positionVec.at(0) << ", " << positionVec.at(1) << ", " << positionVec.at(2) << "}" << std::endl;
    std::cout << "This is Drone's current direction in default constructor: {" << directionVec.at(0) << ", " << directionVec.at(1) << ", " << directionVec.at(2) << "}" << std::endl;

    //flightStrategy = new PathFlight(radius);
    flightStrategy = new ParabolicFlight();
    //flightStrategy = new BeelineFlight();
  }

  void Drone::AddGraphPath(const IGraph* newGraph) {
    dynamic_cast<PathFlight*>(flightStrategy)->AddGraph(newGraph);
  }


  int Drone::GetId() const {
    return id;
  }
  void Drone::SetId(int ID) {
	  id = ID;
  }

  const std::string& Drone::GetName() {
    return name;
  }


  float Drone::GetSpeed() {
    return speed;
  }

  void Drone::SetDirection(std::vector<float> newDirection) {
    direction->SetVector(newDirection);
  }

  void Drone::SetPosition(std::vector<float> newPosition) {
    position->SetVector(newPosition);
  }

  const std::vector<float>& Drone::GetPosition() const {
    return position->GetVector();
  }

  const std::vector<float>& Drone::GetDirection() const {
    return direction->GetVector();
  }

  float Drone::GetRadius() const
  {
    return radius;
  }

  int Drone::GetVersion() const
  {
    return version;
  }

  bool Drone::IsDynamic() const
  {
    return dynamic;
  }

   Package* Drone::GetCurPackage() {
    return curPackage;
  }

  void Drone::UpdateCurPackage() {
    if (assignedPackageIndex < GetNumAssignedPackages()) {
        curPackage = assignedPackages.at(assignedPackageIndex);
    }
    // curPackage = &newPackage;
  }

  void Drone::AddAssignedPackage(Package& newPackage)
  {
    assignedPackages.push_back(&newPackage);
  }

  const bool Drone::GetIsCarryingPackage() const {
    return isCarryingPackage;
  }

  void Drone::SetIsCarryingPackage(bool newIsCarryingPackage) {
    isCarryingPackage = newIsCarryingPackage;
  }

  const bool Drone::GetOnTheWayToPickUpPackage() const {
    return onTheWayToPickUpPackage;
  }

  void Drone::SetOnTheWayToPickUpPackage(bool newOnTheWayToPickUpPackage) {
    onTheWayToPickUpPackage = newOnTheWayToPickUpPackage;
  }

  const bool Drone::GetOnTheWayToDropOffPackage() const {
    return onTheWayToDropOffPackage;
  }

  void Drone::SetOnTheWayToDropOffPackage(bool newOnTheWayToDropOffPackage) {
    onTheWayToDropOffPackage = newOnTheWayToDropOffPackage;
  }

  void Drone::UpdateBatteryCharge(float decrAmount) {
    battery->DecrementCurrentCharge(decrAmount);
  }


  void Drone::UpdateDronePosition(float dt) {
    std::vector<float> directionVec = GetDirection();
    std::vector<float> curPosition = GetPosition();

    float speedAndDt = speed * dt;

    std::vector<float> updateDirection = direction->MultiplyVectorWithFloat(directionVec, speedAndDt);
    std::vector<float> newPosition = position->AddTwoVectors(curPosition, updateDirection);

    // std::cout << "This is Drone new position: {" << newPosition.at(0) << ", " << newPosition.at(1) << ", " << newPosition.at(2) << "}" << std::endl;

    if (battery->GetIsEmpty()==false) {
        position->SetVector(newPosition);

        if (isCarryingPackage) {
          // then also update the package's position
          curPackage->SetPosition(newPosition);
        }
    UpdateBatteryCharge(-dt);
    }
    else {
      // The battery is empty! So we have to announce that the drone/robot is in idle, since it's out of battery
      // also make it drop the package, since it's out of battery...
    }

  }

  void Drone::UpdateDroneVelocity(std::vector<float> &newVelocity) {
    direction->SetVector(newVelocity);
    direction->Normalize();
    if (isCarryingPackage) {
      // then also update the package's velocity
      curPackage->SetVelocity(newVelocity);
    }
  }

  void Drone::Update(const IGraph *graph, std::vector<IEntityObserver *>& observers, float dt)
  {
    std::cout << "These print statements are for Drone name " << name << std::endl;
    std::cout << "===================================" << std::endl;

    if (GetOnTheWayToPickUpPackage() && !GetOnTheWayToDropOffPackage())
    {
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
          const IEntity *temp_drone = this;
          obs->OnEvent(val2, *temp_drone);
          }
        notified=true;}
        else
        { waiter++; }
      }
      std::cout << "I'm on the way to pick up the package" << std::endl;
      // The drone is on the way to pick up a package.
      if (CheckReadyToPickUp())
      {
        PickUpPackage();
        // Update the path so that it's now pointed towards the customer's location

        std::vector<float> currentPos = GetPosition();
        std::vector<float> customerPos = GetCurPackage()->GetDestination();
        flightStrategy->SetFlightDetails(currentPos, customerPos);
        /*
        std::vector<std::vector<float>> anotherRoute = graph->GetPath(GetPosition(), GetCurPackage()->GetDestination());
        SetNewCurRoute(anotherRoute);
        std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
        CalculateAndUpdateDroneDirection(nextPos); */
        //std::cout << "This is Drone's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
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
        ///////// Notifies that it is moving when it picks up the package
        picojson::object obj2 = JsonHelper::CreateJsonObject();
        JsonHelper::AddStringToJsonObject(obj2, "type", "notify");
        JsonHelper::AddStringToJsonObject(obj2, "value", "moving");
        JsonHelper::AddStdVectorVectorFloatToJsonObject(obj2, "path", curRoute);
        picojson::value val2 = JsonHelper::ConvertPicojsonObjectToValue(obj2);
        for (IEntityObserver *obs : observers)
        {
        const IEntity *temp_drone = this;
        obs->OnEvent(val2, *temp_drone);
        }
      }
      else
      {
      /* if (CheckWhenToIncrementPathIndex(curRoute.at(curRouteNextIndex)))
            {
              // We should only increment the path index when the drone gets close enough to it that we should be going to the next one
              std::cout << "I'M JUST INCREMENTING THE PATH INDEX ON THE WAY TO PICK UP THE PACKAGE" << std::endl;
              curRouteNextIndex = curRouteNextIndex + 1;
              std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
              std::cout << "This is Drone's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
              CalculateAndUpdateDroneDirection(nextPos);
            }
            else
            {*/
              // We don't need to increment the path index yet
              //std::cout << "Don't need to increment path index yet" << std::endl;
              //std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
              //std::cout << "This is Drone's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
        // CalculateAndUpdateDroneDirection(nextPos);
        // }
      }
      std::vector<float> &tmpPos = const_cast<std::vector<float>&>(GetPosition());
      std::vector<float> &tmpDir = const_cast<std::vector<float>&>(GetDirection());
      float speed_dt = (GetSpeed() * dt);
      flightStrategy->FlightUpdate(speed_dt, tmpPos, tmpDir);
      //UpdateDronePosition(dt);
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


        ///////// Notifies that it is idle since dropped off package
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
        /////////////

        // if there's another package it has to go to, then assign this new package to the curPackage
        if (assignedPackageIndex < GetNumAssignedPackages()) {
          UpdateCurPackage();
          //std::vector<std::vector<float>> anotherRoute = graph->GetPath(GetPosition(), curPackage->GetPosition());
          //SetNewCurRoute(anotherRoute);
	        flightStrategy->SetFlightDetails(GetPosition(), GetCurPackage()->GetPosition());
          SetOnTheWayToPickUpPackage(true);
          SetOnTheWayToDropOffPackage(false);
        }
      }
      else
      {/*
        if (CheckWhenToIncrementPathIndex(curRoute.at(curRouteNextIndex)))
        {
          curRouteNextIndex = curRouteNextIndex + 1;
          std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
          CalculateAndUpdateDroneDirection(nextPos);
        }
        else
        {
          // We don't need to increment the path index yet
          std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
          CalculateAndUpdateDroneDirection(nextPos);
	      }*/

        //capture the refrences to this drone's position and direction to use in FlightUpdate()
        std::vector<float> &tmpPos = const_cast<std::vector<float>&>(GetPosition());
        std::vector<float> &tmpDir = const_cast<std::vector<float>&>(GetDirection());
        float speed_dt = (GetSpeed() * dt);
        flightStrategy->FlightUpdate(speed_dt, tmpPos, tmpDir);
              //UpdateDronePosition(dt);
        if (isCarryingPackage) {
          std::vector<float> newPos = (GetPosition());
          //Package* tmp = con
          GetCurPackage()->SetPosition(newPos);
        }
      }
    }
  }

  bool Drone::CheckReadyToPickUp()
  {
    std::vector<float> currentPosition = GetPosition();
    std::vector<float> packagePosition = curPackage->GetPosition();
    std::cout << "I am in Drone::CheckReadyToPickUp checking the curPackage's position" << std::endl;
    int i = 0;
    int numWithinRadius = 0;
    std::cout << "This is Drone's current position in CheckReadyToPickUp: {" << currentPosition.at(0) << ", " << currentPosition.at(1) << ", " << currentPosition.at(2) << "}" << std::endl;
    std::cout << "This is Package's current position in CheckReadyToPickUp: {" << packagePosition.at(0) << ", " << packagePosition.at(1) << ", " << packagePosition.at(2) << "}" << std::endl;
    for(float pos : currentPosition) {
      float packagePos = packagePosition.at(i);
      i = i + 1;
      // std::cout << "I am about to subtract the package position from the position" << std::endl;
      if (std::fabs(pos - packagePos) <= radius * 2.0) {
        // std::cout << "I am in the pos - packagePos <= radius condition" << std::endl;
        numWithinRadius = numWithinRadius + 1;
      }
      // std::cout << "I am done subtracting the package position from the position" << std::endl;
    }
    if (numWithinRadius == 2) {
      std::cout << "The package is ready to be picked up!" << std::endl;
      return true;
    } else {
    return false;
    }
  }

  bool Drone::CheckReadyToDropOff() {
    std::vector<float> currentPosition = GetPosition();
    std::vector<float> packageDestination = curPackage->GetDestination();
    std::vector<float> packagePosition = curPackage->GetPosition();
    std::vector<float> customerPosition = curPackage->GetDestination();
    int i = 0;
    int numWithinRadius = 0;
    std::cout << "This is Drone's current position in CheckReadyToDropOff: {" << currentPosition.at(0) << ", " << currentPosition.at(1) << ", " << currentPosition.at(2) << "}" << std::endl;
    std::cout << "This is Package's current position in CheckReadyToDropOff: {" << packagePosition.at(0) << ", " << packagePosition.at(1) << ", " << packagePosition.at(2) << "}" << std::endl;
    std::cout << "This is Customer's current position in CheckReadyToDropOff: {" << customerPosition.at(0) << ", " << customerPosition.at(1) << ", " << customerPosition.at(2) << "}" << std::endl;

    for (float pos : currentPosition)
    {
      float packageDes = packageDestination.at(i);
      i = i + 1;
      if (std::fabs(pos - packageDes) <= radius * 2.0)
      {
        numWithinRadius = numWithinRadius + 1;
      }
    }
    if (numWithinRadius == 2)
    {
      std::cout << "The package is ready to be dropped off!" << std::endl;
      return true;
    }
    else
    {
      return false;
    }
  }

  bool Drone::CheckWhenToIncrementPathIndex(std::vector<float>& nextPosition)
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

  void Drone::PickUpPackage() {
    isCarryingPackage = true;
    onTheWayToPickUpPackage = false;
    onTheWayToDropOffPackage = true;
  }

  void Drone::DropOffPackage() {
    isCarryingPackage = false;
    std::vector<float> outOfTheWayPosition{10, 1000, 10};
    curPackage->SetPosition(outOfTheWayPosition);
    onTheWayToPickUpPackage = false;
    onTheWayToDropOffPackage = false;
	  notified = false;
	  waiter = 0;
    // also set the drone's direction to 0,0,0 so that we stop moving
    std::vector<float> stopMoving{0.0001,0.0001,0.0001};
    UpdateDroneVelocity(stopMoving);
    curPackage->SetVelocity(stopMoving);
    // increment the package index to see if there are any other packages that should be picked up
    assignedPackageIndex = assignedPackageIndex + 1;
    std::cout << "I've dropped off the package" << std::endl;
  }

  void Drone::CalculateAndUpdateDroneDirection(std::vector<float> &nextPosition) {
    std::vector<float> currentPosition = position->GetVector();
    std::vector<float> newVelocity = position->SubtractTwoVectors(nextPosition, currentPosition);
    UpdateDroneVelocity(newVelocity);
  }

  int Drone::GetNumAssignedPackages() {
    return assignedPackages.size();
  }

  void Drone::SetNewCurRoute(std::vector<std::vector<float>> &newCurRoute) {
    // resets the curRoute
    curRoute = newCurRoute;
    curRouteLength = curRoute.size();
    curRouteNextIndex = 1;
  }

  int Drone::GetCurRouteLength() {
    return curRouteLength;
  }

  int Drone::GetCurRouteNextIndex() {
    return curRouteNextIndex;
  }

  void Drone::IncrementCurRouteNextIndex() {
    curRouteNextIndex = curRouteNextIndex + 1;
  }

  void Drone::SetFlightBehavior(std::vector<float> pos, std::vector<float> target, IGraph* newGraph) {
    flightStrategy->SetFlightDetails(pos, target, newGraph);
  }
}

#include "package.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "customer.h"
#include "json_helper.h"
#include <cmath>
#include <iostream>

namespace csci3081
{

  Package::Package(const picojson::object &obj)
  {
	
	id = rand();
	
    //std::cout << "This is package ID: " << packageId << std::endl;
    name = JsonHelper::GetString(obj, "name");
    std::vector<float> position = JsonHelper::GetStdFloatVector(obj, "position");
    std::vector<float> direction = JsonHelper::GetStdFloatVector(obj, "direction");
    positionAndDirection = new Vector3D(position, direction);
    radius = (float)JsonHelper::GetDouble(obj, "radius");
    weight = 0.0;

    details_ = obj;

    std::cout << "In the package default constructor" << std::endl;
  }

  int Package::GetId() const
  {
    return id;
  }

  const std::string &Package::GetName()
  {
    return name;
  }

  const std::vector<float> &Package::GetPosition() const
  {
    // std::cout << "I'm in package getposition" << std::endl;
    return positionAndDirection->GetPosition();
  }

  void Package::SetPosition(std::vector<float> &newPosition)
  {
    positionAndDirection->SetPosition(newPosition);
  }

  const std::vector<float> &Package::GetDirection() const
  {
    return positionAndDirection->GetDirection();
  }

  void Package::SetVelocity(std::vector<float> &newVelocity)
  {
    positionAndDirection->SetVelocity(newVelocity);
  }

  float Package::GetRadius() const
  {
    return radius;
  }

  int Package::GetVersion() const
  {
    return version;
  }

  bool Package::IsDynamic() const
  {
    return true;
  }

  void Package::SetCustomer(Customer &newCustomer) {
    customer = &newCustomer;
    destination = customer->GetPosition();
  }

  const Customer Package::GetCustomer() {
    return *customer;
  }

  const std::vector<float> Package::GetDestination() const {
    return destination;
  }

  float Package::GetWeight() {
    return weight;
  }
}

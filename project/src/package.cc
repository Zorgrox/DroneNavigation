#include "package.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "customer.h"
#include "json_helper.h"
#include <iostream>

namespace csci3081
{

  Package::Package(const picojson::object &obj)
  {
    //std::cout << "This is package ID: " << packageId << std::endl;
    name = JsonHelper::GetString(obj, "name");
    std::vector<float> positionVec = JsonHelper::GetStdFloatVector(obj, "position");
    std::vector<float> directionVec = JsonHelper::GetStdFloatVector(obj, "direction");
    position = new Vector3D(positionVec);
    direction = new Vector3D(directionVec);
    direction->Normalize();
    // std::cout << "Here's the direction of package:" << directionVec.at(0) << ", " << directionVec.at(1) << ", " << directionVec.at(2) << std::endl;
    radius = (float)JsonHelper::GetDouble(obj, "radius");
    weight = 0.0;

    details_ = obj;

    // std::cout << "In the package default constructor" << std::endl;
  }

  int Package::GetId() const
  {
    return id;
  }
  void Package::SetId(int ID) {
	  id = ID;
  }

  const std::string &Package::GetName()
  {
    return name;
  }

  const std::vector<float> &Package::GetPosition() const
  {
    return position->GetVector();
  }

  void Package::SetPosition(std::vector<float> &newPosition)
  {
    position->SetVector(newPosition);
  }

  const std::vector<float> &Package::GetDirection() const
  {
    return direction->GetVector();
  }

  void Package::SetVelocity(std::vector<float> &newVelocity)
  {
    direction->SetVector(newVelocity);
    direction->Normalize();
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
    if (customer == NULL) {
      std::cout << "customer in package setcustomer is null" << std::endl;
    }
    destination = customer->GetPosition();
  }

  Customer* Package::GetCustomer() {
    return customer;
  }

  const std::vector<float> Package::GetDestination() const {
    return destination;
  }

  float Package::GetWeight() {
    return weight;
  }
}

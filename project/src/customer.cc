#include "customer.h"
#include "json_helper.h"
#include "vector3d.h"
#include <cmath>
#include <iostream>

namespace csci3081
{
  Customer::Customer(const picojson::object &obj)
  {
	//srand(time(0));
	id = rand();
    
    //std::cout << "This is customer ID: " << customerId << std::endl;
    name = JsonHelper::GetString(obj, "name");
    std::vector<float> position = JsonHelper::GetStdFloatVector(obj, "position");
    std::vector<float> direction = JsonHelper::GetStdFloatVector(obj, "direction");
    positionAndDirection = new Vector3D(position, direction);
    radius = (float) JsonHelper::GetDouble(obj, "radius");

    details_ = obj;
  }

  int Customer::GetId() const
  {
    return id;
  }

  const std::string &Customer::GetName()
  {
    return name;
  }

  const std::vector<float> &Customer::GetPosition() const
  {
    if (positionAndDirection) {
      return positionAndDirection->GetPosition();
    } else {
      std::cout << "positionAndDirection in Customer is NULL" << std::endl;
    }
  }

  const std::vector<float> &Customer::GetDirection() const
  {
    return positionAndDirection->GetDirection();
  }

  float Customer::GetRadius() const
  {
    return radius;
  }

  int Customer::GetVersion() const
  {
    return version;
  }

  bool Customer::IsDynamic() const
  {
    return dynamic;
  }

}

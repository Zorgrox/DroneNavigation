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
    std::vector<float> positionVec = JsonHelper::GetStdFloatVector(obj, "position");
    std::vector<float> directionVec = JsonHelper::GetStdFloatVector(obj, "direction");
    position = new Vector3D(positionVec);
    direction = new Vector3D(directionVec);
    direction->Normalize();
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
    if (position)
    {
      return position->GetVector();
    }
    else
    {
      std::cout << "position in Customer is NULL" << std::endl;
    }
  }

  const std::vector<float> &Customer::GetDirection() const
  {
    return direction->GetVector();
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

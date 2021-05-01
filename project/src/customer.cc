#include "customer.h"
#include "json_helper.h"
#include "vector3d.h"
#include <iostream>

namespace csci3081
{
  Customer::Customer(const picojson::object &obj)
  {
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

  Customer::~Customer() {
    delete position;
    delete direction;
  }

  int Customer::GetId() const
  {
    return id;
  }

  void Customer::Update(const IGraph *graph, std::vector<IEntityObserver *> &observers, float dt) {}

  void Customer::SetId(int ID) {
	  id = ID;
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

#include "drone.h"

namespace csci3081 {

Drone::Drone(std::vector<float> position, std::vector<float> direction, 
                                        const picojson::object& details) {
  // TODO for lab10: store the position and direction vectors.

  // The following line saves the json object in the details_ member variable
  // from the EntityBase class, in order to return it later in GetDetails()
  details_ = details;
}

int Drone::GetId() const {
  // TODO: This is just a stub for compilation
  return 0;
}

const std::string& Drone::GetName() {
  // TODO for lab10: What should this return?
}

const std::vector<float>& Drone::GetPosition() const {
  // TODO for lab10: What should this return?
}

const std::vector<float>& Drone::GetDirection() const {
  // TODO for lab10: what should this return?
}

float Drone::GetRadius() const {
  // TODO: This is just a stub for compilation
  return 1;
}

int Drone::GetVersion() const {
  // TODO: This is just a stub for compilation
  return 0;
}

bool Drone::IsDynamic() const {
  // TODO: This is just a stub for compilation
  return true;
}

}
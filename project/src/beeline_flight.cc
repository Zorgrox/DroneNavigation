
#include "beeline_flight.h"


namespace csci3081 {

  BeelineFlight::BeelineFlight() {  }

  void BeelineFlight::FlightUpdate(float speedANDdt, std::vector<float>& pos, std::vector<float>& dir) {
    //increment drone x,z position by the stored direction and it's speed and dt time
    Vector3D Tmp(pos);
    std::vector<float> currentPosition = pos;
    std::vector<float> target = flightTarget;
    std::vector<float> newDirection = Tmp.SubtractTwoVectors(target, currentPosition);

    //saves and normalizes direction vector for later
    Vector3D Direction(newDirection);
    Direction.Normalize();
    newDirection = Direction.GetVector();
    //float speedAndDT = drone_self->GetSpeed() * dt;
    newDirection = Direction.MultiplyVectorWithFloat(newDirection,speedANDdt);
    //newDirection now contains the x,z movement offset and will be added to the drone's position
    currentPosition = Direction.AddTwoVectors(currentPosition, newDirection);
    // sets the vectors at input refrence pos and dir to the intended position and direction
    pos = currentPosition;
    std::vector<float> tmp = Direction.GetVector();
    dir = tmp;
  }

  void BeelineFlight::SetFlightDetails(std::vector<float> pos,std::vector<float> target,  IGraph* newGraph) {
    SetFlightDetails(pos, target);
  }

  void BeelineFlight::SetFlightDetails(std::vector<float> pos, std::vector<float> target) {
    // Setting target position saved as float vector flightTarget
    flightTarget = target;
    //std::cout << "madehere\n";
  }

}

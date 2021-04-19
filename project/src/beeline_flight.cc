
#include "beeline_flight.h"


namespace csci3081 {

  BeelineFlight::BeelineFlight() {  }

  void BeelineFlight::FlightUpdate(float speedANDdt, std::vector<float>& pos, std::vector<float>& dir) {
 if (pos.at(1)<280) {pos.at(1)+=.1;} // Cause the drone to rise, to fly over buildings
 else {

  //increment drone x,y,z position by the stored direction and it's speed and dt time
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

  }

  void BeelineFlight::SetFlightDetails(std::vector<float> pos,std::vector<float> target, const IGraph* newGraph) {
    SetFlightDetails(pos, target);
  }

  void BeelineFlight::SetFlightDetails(std::vector<float> pos, std::vector<float> target) {
    // Setting target position saved as float vector flightTarget
    flightTarget = target;
    //std::cout << "madehere\n";
    SetCurRoute(pos, target);
  }

  float BeelineFlight::CalculateDistance (std::vector<float> pos, std::vector<float> target) {
      // calculate distance to package from only x and z (y has to be ignored)
      float xDist = target.at(0) -pos.at(0);
      float yDist = target.at(1) - pos.at(1);
      float zDist = target.at(2) - pos.at(2);
      float distance = sqrt(pow((xDist),2.0)+pow((yDist),2.0)+pow((zDist),2.0));
      return distance;
  }

  void BeelineFlight::SetCurRoute(std::vector<float> pos, std::vector<float> target) {
    std::vector<std::vector<float>> tmpRoute;
    float tripDistance = CalculateDistance(pos,target);
    for (int i(0); i <= 30; i++) {
      Vector3D Tmp(pos);
      std::vector<float> currentPosition = pos;
      std::vector<float> newDirection = Tmp.SubtractTwoVectors(target, currentPosition);

      //saves and normalizes direction vector for later
      Vector3D Direction(newDirection);
      Direction.Normalize();
      newDirection = Direction.GetVector();
      //float speedAndDT = drone_self->GetSpeed() * dt;
      newDirection = Direction.MultiplyVectorWithFloat(newDirection,(i * tripDistance) / 30.0);
      //newDirection now contains the x,z movement offset and will be added to the drone's position
      currentPosition = Direction.AddTwoVectors(currentPosition, newDirection);
      // sets the vectors at input refrence pos and dir to the intended position and direction

      tmpRoute.push_back(currentPosition);

    }

    curRoute = tmpRoute;

  }

  std::vector<std::vector<float>> BeelineFlight::GetCurRoute() {
	  return curRoute;
  }


}

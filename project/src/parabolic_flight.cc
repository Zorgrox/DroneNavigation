
#include "parabolic_flight.h"
#include "drone.h"

namespace csci3081 {

  ParabolicFlight::ParabolicFlight() {  }

  void ParabolicFlight::FlightUpdate(float speedANDdt, std::vector<float>& pos, std::vector<float>& dir) {
    //increment drone x,z position by the stored direction and it's speed and dt time
    Vector2D Tmp(pos);
    std::vector<float> currentPosition = pos;
    std::vector<float> target = flightTarget;
    std::vector<float> newDirection = Tmp.SubtractTwoVectors(target, currentPosition);

    //saves and normalizes direction vector for later
    Vector2D Direction(newDirection);
    Direction.Normalize();
    newDirection = Direction.GetVector();
    newDirection = Direction.MultiplyVectorWithFloat(newDirection,speedANDdt);
    //newDirection now contains the x,z movement offset and will be added to the drone's position
    currentPosition = Direction.AddTwoVectors(currentPosition, newDirection);
    //then calculate and increment to the appropriate y position.

    std::cout << "In Parabolic FlightUpdate: \n";
    float distance = CalculateDistance(pos,target);
    //calculate incrementY
    std::cout << "Trip Distance: " << tripDistance <<std::endl;
    float x = abs((distance)-(tripDistance / 2.0));
    std::cout << "x: " << x <<std::endl;
    std::cout << "Extender: " << extender <<std::endl;
    std::cout << "Extender * x^2: " << extender*(x*x) <<std::endl;
    float incrementY = (extender * (x * x) + parabolicHeight);
    std::cout << "increment Y: " << incrementY <<std::endl;
    std::cout << "initial Y: " << initialY <<std::endl;
    float intendedY = initialY + incrementY;
    std::cout << "intended Y: " << intendedY <<std::endl;
    float dronesX = currentPosition.at(0);
    float dronesZ = currentPosition.at(2);
    std::vector<float> parabolicYPos{dronesX, intendedY, dronesZ};

    // sets the vectors at input refrence pos and dir to the intended position and direction
    pos = parabolicYPos;
    std::vector<float> tmp = Direction.GetVector();
    dir = tmp;
  }

  float ParabolicFlight::CalculateDistance (std::vector<float> pos, std::vector<float> target) {
      // calculate distance to package from only x and z (y has to be ignored)
      float xDist = target.at(0) -pos.at(0);
      float yDist = target.at(2) - pos.at(2);
      float distance = sqrt(pow((xDist),2.0)+pow((yDist),2.0));
      return distance;
  }

  void ParabolicFlight::SetFlightDetails(std::vector<float> pos, std::vector<float> target) {
    //First Setting "beeline" details aka target position saved as float vector flightTarget
    //std::vector<float> currentPosition = drone_self->GetPosition();
    //std::vector<float> newDirection = flightTarget->SubtractTwoVectors(target, currentPosition);
    //flightTarget->SetVector(newDirection);
    //flightTarget->Normalize();

    //Now setting the variables in the parabola equation:
    std::cout << "Scheduling Parabolic flight\n";
    tripDistance = CalculateDistance(pos, target);
    std::cout << "Trip Distance: " << tripDistance << std::endl;
    //parabolic height is currently set here as 10% of the trip distance
    parabolicHeight = tripDistance * 0.15;
    std::cout << "Parabola Height: " << parabolicHeight << std::endl;
    initialY = pos.at(1);
    std::cout << "initial Y-value: " << initialY << std::endl;
    extender = - (parabolicHeight / ((tripDistance/2.0) *( tripDistance/2.0)));
    std::cout << "Extender: " << extender << std::endl;
    flightTarget = target;
    SetCurRoute(pos,target);
  }

void ParabolicFlight::SetCurRoute(std::vector<float> pos, std::vector<float> target) {
  // for 31 intervals, calculate the position of a path node and add to the vector
  std::vector<std::vector<float>> tmpRoute;
  for (int i(0); i <= 30; i++) {
    //calculate the temp node position at the i/30th distance
    Vector2D Tmp(pos);
    std::vector<float> currentPosition = pos;
    std::vector<float> newDirection = Tmp.SubtractTwoVectors(target, currentPosition);
    //from pos to target, add i/30 increment of the distance using vector2D math
     Vector2D Direction(newDirection);
    Direction.Normalize();
    newDirection = Direction.GetVector();

    newDirection = Direction.MultiplyVectorWithFloat(newDirection, (i * tripDistance / 30) );
    //newDirection now contains the x,z movement offset and will be added to the drone's original position
    currentPosition = Direction.AddTwoVectors(currentPosition, newDirection);

    std::cout << "Creating Parabolic Offset in SetFlightDetails\n";
    //next calculate and apply the parabolic y-axis offset
    float distance = (i * tripDistance / 30);
    //calculate incrementY
    std::cout << "Trip Distance: " << tripDistance <<std::endl;
    float x = abs((distance)-(tripDistance / 2.0));
    std::cout << "x: " << x <<std::endl;
    std::cout << "Extender: " << extender <<std::endl;
    std::cout << "Extender * x^2: " << extender*(x*x) <<std::endl;
    float incrementY = (extender * (x * x) + parabolicHeight);
    std::cout << "increment Y: " << incrementY <<std::endl;
    std::cout << "initial Y: " << initialY <<std::endl;
    float intendedY = initialY + incrementY;
    std::cout << "intended Y: " << intendedY <<std::endl;
    float dronesX = currentPosition.at(0);
    float dronesZ = currentPosition.at(2);
    std::vector<float> parabolicYPos{dronesX, intendedY, dronesZ};
    std::cout << parabolicYPos[0] << " " << parabolicYPos[1] << " " << parabolicYPos[2] << std::endl;
    //apply the y-axis offset
    currentPosition[1] = intendedY;
    //push_back the temp position node onto the tmpRoute
    tmpRoute.push_back(parabolicYPos);

  }
  curRoute = tmpRoute;
}

void ParabolicFlight::SetFlightDetails(std::vector<float> pos,std::vector<float> target, const IGraph* newGraph) {
  SetFlightDetails(pos, target);
}

std::vector<std::vector<float>> ParabolicFlight::GetCurRoute()
{
  return curRoute;
}
} // namespace csci3081w

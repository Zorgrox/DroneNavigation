
#include "path_flight.h"

namespace csci3081 {

  PathFlight::PathFlight() {  }

  PathFlight::PathFlight(float newRadius) {
    this->radius = newRadius;
  }

  void PathFlight::FlightUpdate(float speedANDdt, std::vector<float>& pos, std::vector<float>& dir) {

    std::vector<float> nextPos;
    if (CheckWhenToIncrementPathIndex(curRoute.at(curRouteNextIndex), pos)) {
          // We should only increment the path index when the drone gets close enough to it that we should be going to the next one
          curRouteNextIndex = curRouteNextIndex + 1;
          nextPos = curRoute.at(curRouteNextIndex);
          //CalculateAndUpdateDroneDirection(nextPos);
	       
        } else {
          // We don't need to increment the path index yet
          nextPos = curRoute.at(curRouteNextIndex);
	 }

    //increment drone x,y,z position by the stored direction and it's speed and dt seconds
    Vector3D utility(pos);
    std::vector<float> currentPosition = pos;

    //in path mode target is next node in the path calculated above
    std::vector<float> target = nextPos;
    std::vector<float> newDirection = utility.SubtractTwoVectors(target, currentPosition);

    //saves and normalizes direction vector for later
    Vector3D Direction(newDirection);
    Direction.Normalize();
    newDirection = Direction.GetVector();

    newDirection = Direction.MultiplyVectorWithFloat(newDirection,speedANDdt);
    //newDirection now contains the x,z movement offset and will be added to the drone's position
    currentPosition = Direction.AddTwoVectors(currentPosition, newDirection);

    // sets the vectors at input refrence pos and dir to the intended position and direction
    pos = currentPosition;
    std::vector<float> tmp = Direction.GetVector();
    dir = tmp;
}

  float PathFlight::CalculateDistance (std::vector<float> pos, std::vector<float> target) {
      //calculate distance to package from x, y, z
      float xDist = target.at(0) -pos.at(0);
      float yDist = target.at(1) -pos.at(1);
      float zDist = target.at(2) - pos.at(2);
      float distance = sqrt(pow((xDist),2.0)+pow((yDist),2.0)+pow((zDist),2.0));
      return distance;
  }

  void PathFlight::SetFlightDetails(std::vector<float> pos, std::vector<float> target, const IGraph* newGraph) {
    graph = newGraph;
    flightTarget = target;
    SetCurRoute(pos, target);
    std::cout << "madehereP1\n";
}
  void PathFlight::SetFlightDetails(std::vector<float> pos, std::vector<float> target) {
     flightTarget = target;
     SetCurRoute(pos, target);
     std::cout << "madehereP2\n";
  }


  bool PathFlight::CheckWhenToIncrementPathIndex(std::vector<float> &nextPosition, std::vector<float> position) {

    //std::vector<float> currentPosition = GetPosition();
    float distance = CalculateDistance(position, nextPosition);
    if (distance <= radius * 2.0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void PathFlight::AddGraph(const IGraph* newGraph) {
    graph = newGraph;
  }

  void PathFlight::SetCurRoute(std::vector<float> pos, std::vector<float> target) {
    // resets the curRoute
    std::vector<std::vector<float>> newCurRoute = graph->GetPath(pos, target);
    curRoute = newCurRoute;
    curRouteLength = curRoute.size();
    curRouteNextIndex = 1;
  }

  void PathFlight::SetCurRouteTest(std::vector<std::vector<float>> newCurRoute) {
    // resets the curRoute
    curRoute = newCurRoute;
    curRouteLength = curRoute.size();
    curRouteNextIndex = 1;
  }

  std::vector<std::vector<float>> PathFlight::GetCurRoute()
  {
	  return curRoute;
  }

}

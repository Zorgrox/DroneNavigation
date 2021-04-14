
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
          std::cout << "I'M JUST INCREMENTING THE PATH INDEX ON THE WAY TO PICK UP THE PACKAGE" << std::endl;
          curRouteNextIndex = curRouteNextIndex + 1;
          nextPos = curRoute.at(curRouteNextIndex);
          std::cout << "This is Drone/Robot's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
          //CalculateAndUpdateDroneDirection(nextPos);
	        //fix
        } else {
          // We don't need to increment the path index yet
          std::cout << "Don't need to increment path index yet" << std::endl;
          nextPos = curRoute.at(curRouteNextIndex);
          std::cout << "This is Drone/Robot's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
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

  void PathFlight::SetFlightDetails(std::vector<float> pos, std::vector<float> target,  IGraph* newGraph) {
    graph = newGraph;
    flightTarget = target;
     std::vector<std::vector<float>> anotherRoute = graph->GetPath(pos, target);
    SetNewCurRoute(anotherRoute);
    std::cout << "madehereP1\n";
    //std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
    //CalculateAndUpdateDroneDirection(nextPos);
}
  void PathFlight::SetFlightDetails(std::vector<float> pos, std::vector<float> target) {
     flightTarget = target;
     std::vector<std::vector<float>> anotherRoute = graph->GetPath(pos, target);
     SetNewCurRoute(anotherRoute);
     std::cout << "madehereP2\n";
  }


  bool PathFlight::CheckWhenToIncrementPathIndex(std::vector<float> &nextPosition, std::vector<float> position) {
    std::cout << "I am checking when to increment the path index" << std::endl;

    //std::vector<float> currentPosition = GetPosition();
    float distance = CalculateDistance(position, nextPosition);
    std::cout << "distance: " << distance << std::endl;
    if (distance <= radius * 2.0)
    {
      std::cout << "It is within radius to increment path index" << std::endl;
      return true;
    }
    else
    {
      std::cout << "It is NOT within radius to increment path index" << std::endl;
      return false;
    }
  }

  void PathFlight::SetNewCurRoute(std::vector<std::vector<float>> &newCurRoute) {
    // resets the curRoute
    curRoute = newCurRoute;
    curRouteLength = curRoute.size();
    curRouteNextIndex = 1;
  }

  void PathFlight::AddGraph(const IGraph* newGraph) {
    graph = newGraph;
  }

}

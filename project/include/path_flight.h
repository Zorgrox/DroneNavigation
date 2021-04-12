
#ifndef PATH_FLIGHT_H
#define PATH_FLIGHT_H


#include <vector>
#include "vector3d.h"
#include "flight_behavior.h"
#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {

class PathFlight : public FlightBehavior {
	public:
		PathFlight();
		PathFlight(float radius);
		
		
		void AddGraph(const IGraph *systemGraph);
		
		void FlightUpdate(float dt, std::vector<float>& pos, std::vector<float>& dir);
		
		void SetFlightDetails(std::vector<float> pos,std::vector<float> target,  IGraph* newGraph);
		
		void SetFlightDetails(std::vector<float> pos,std::vector<float> target);
		
		float CalculateDistance(std::vector<float> pos,std::vector<float> target);
		
		bool CheckWhenToIncrementPathIndex(std::vector<float> &nextPosition, std::vector<float> position);
		
		void SetNewCurRoute(std::vector<std::vector<float>> &newPosition);
	
	private:
	const IGraph *graph;
	std::vector<float> flightTarget;
	
	std::vector<std::vector<float>> curRoute;
	int curRouteNextIndex;
    	int curRouteLength;
    	float radius;
	
};

}

#endif



#ifndef BEELINE_FLIGHT_H
#define BEELINE_FLIGHT_H

#include <vector>
#include "flight_behavior.h"
#include "vector3d.h"


namespace csci3081 {

class BeelineFlight : public FlightBehavior {
	public:
		BeelineFlight();
		
		void FlightUpdate(float speedANDdt, std::vector<float>& pos, std::vector<float>& dir);
		
		void SetFlightDetails(std::vector<float> pos,std::vector<float> target,  IGraph* newGraph);
		
		void SetFlightDetails(std::vector<float> pos,std::vector<float> target);
		
		
		
	private:
	std::vector<float> flightTarget;
	
};
}
#endif



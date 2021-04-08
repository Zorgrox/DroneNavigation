
#ifndef PARABOLIC_FLIGHT_H
#define PARABOLIC_FLIGHT_H

#include <vector>
#include "flight_behavior.h"
#include "vector2d.h"
//#include "drone.h"

namespace csci3081 {

class ParabolicFlight : public FlightBehavior {
	public:
		ParabolicFlight();
		
		void FlightUpdate(float dt, std::vector<float>& pos, std::vector<float>& dir);
		
		void SetFlightDetails(std::vector<float> pos,std::vector<float> target);
		
		float CalculateDistance(std::vector<float> pos,std::vector<float> target);
		
	private:
	//Drone* drone_self;
	std::vector<float> flightTarget;
	float parabolicHeight;
	float initialY;
	float tripDistance;
	float extender;
};

}

#endif

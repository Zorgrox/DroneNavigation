	  
#ifndef FLIGHT_BEHAVIOR_H
#define FLIGHT_BEHAVIOR_H

//#include "drone.h"

namespace csci3081 {

//The FlightBehavior Fascade is simple, use SetFlightDetails whenever the drone's target needs to be set, and call FlightUpdate to update the drone's position based on internal data and dt
class FlightBehavior {
	public:
	virtual void FlightUpdate(float dt, std::vector<float>& pos, std::vector<float>& dir) = 0;
	virtual void SetFlightDetails(std::vector<float> pos, std::vector<float> target) = 0;
	//protected:
	//	Drone* drone_self;
};

}

#endif

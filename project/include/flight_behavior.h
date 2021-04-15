/**
 * @file flight_behavior.h
 */
#ifndef FLIGHT_BEHAVIOR_H
#define FLIGHT_BEHAVIOR_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the flight behavior interface that all of the different flight behavior strategies will inherit from.
 *
 * The FlightBehavior Fascade is simple, use SetFlightDetails whenever the drone's target needs to be set, and call FlightUpdate to update the drone/robot's position based on internal data and dt.
 */

  class FlightBehavior
  {
	public:
    /**
     *  This function is called to update the drone/robot's position, based on the particular strategy
     */
    virtual void FlightUpdate(float dt, std::vector<float> &pos, std::vector<float> &dir) = 0;
    /**
     *  This function is used whenever the drone's target needs to be set. This one is specifically used for the smart route.
     */
    virtual void SetFlightDetails(std::vector<float> pos, std::vector<float> target, IGraph *newGraph) = 0;
    /**
     *  This function is used whenever the drone's target needs to be set, for flights that do not need the smart route Graph.
     */
    virtual void SetFlightDetails(std::vector<float> pos, std::vector<float> target) = 0;
};

} // namespace csci3081

#endif // FLIGHT_BEHAVIOR_H

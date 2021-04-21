/**
 * @file beeline_flight.h
 */
#ifndef BEELINE_FLIGHT_H
#define BEELINE_FLIGHT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "flight_behavior.h"
#include "vector3d.h"


namespace csci3081 {
  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the beeline path flight strategy for the movement for the drone/robot, where the drone/robot takes a straight line route from its position to the specified destination.
 *
 */

  class BeelineFlight : public FlightBehavior
  {
    public:
      /**
        *  @brief Constructor: set up Beeline Flight
        */
      BeelineFlight();

      /**
        *  This function is called to update the drone/robot's position, based on the beeline straight path route
        * @param speedANDdt the value of the speed multiplied by the dt (difference in time between calls to the Update function)
        * @param pos the position
        * @param dir the direction
        */
      void FlightUpdate(float speedANDdt, std::vector<float>& pos, std::vector<float>& dir);

      /**
        * This function is used whenever the target needs to be set. This one is specifically used for the smart route.
        * @param pos the current position
        * @param target the intended target position of the flight
        * @param newGraph the graph for calculating smart route, if needed
        */
      void SetFlightDetails(std::vector<float> pos,std::vector<float> target, const IGraph* newGraph);

      /**
        *  This function is used whenever the target needs to be set, for flights that do not need the smart route Graph.
        * @param pos the current position
        * @param target the intended target position of the flight
        */
      void SetFlightDetails(std::vector<float> pos,std::vector<float> target);

      /**
       *  This function is used to calculate and return the distance from the drone/robot to the package or customer.
       * @param pos the current position
       * @param target the intended target position of the flight
       */
      float CalculateDistance(std::vector<float> pos,std::vector<float> target);

      /**
       *  This function is used to set the current route.
       * @param pos the current position
       * @param target the intended target position of the flight
       */
      void SetCurRoute(std::vector<float> pos,std::vector<float> target);

	    /**
        *  This function is used to return the current route.
        */
	    std::vector<std::vector<float>> GetCurRoute();

    private:
      std::vector<float> flightTarget;

  };

} // namespace csci3081

#endif // BEELINE_FLIGHT_H

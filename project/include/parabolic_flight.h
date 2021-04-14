/**
 * @file parabolic_flight.h
 */
#ifndef PARABOLIC_FLIGHT_H
#define PARABOLIC_FLIGHT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "flight_behavior.h"
#include "vector2d.h"

namespace csci3081 {
  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the parabolic flight strategy for the movement for the drone/robot.
 *
 */

  class ParabolicFlight : public FlightBehavior
  {
    public:
      /**
       *  @brief Constructor: set up Parabolic Flight
       */
      ParabolicFlight();

      /**
       *  This function is called to update the drone/robot's position, based on the parabolic flight strategy
       */
      void FlightUpdate(float dt, std::vector<float>& pos, std::vector<float>& dir);

      /**
       *  This function is used whenever the drone's target needs to be set. This one is specifically used for the smart route.
       */
      void SetFlightDetails(std::vector<float> pos,std::vector<float> target,  IGraph* newGraph);

      /**
       *  This function is used whenever the drone's target needs to be set, for flights that do not need the smart route Graph.
       */
      void SetFlightDetails(std::vector<float> pos,std::vector<float> target);

      /**
       *  This function is used to calculate and return the distance from the drone/robot to the package from only x and z (y has to be ignored)
       */
      float CalculateDistance(std::vector<float> pos,std::vector<float> target);

    private:
      std::vector<float> flightTarget;
      float parabolicHeight;
      float initialY;
      float tripDistance;
      float extender;
  };

} // namespace csci3081

#endif // PARABOLIC_FLIGHT_H

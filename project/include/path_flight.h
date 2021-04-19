/**
 * @file path_flight.h
 */
#ifndef PATH_FLIGHT_H
#define PATH_FLIGHT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "vector3d.h"
#include "flight_behavior.h"
#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {
  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the smart route path flight strategy for the movement for the drone/robot, where the drone/robot follows the route specified by the smart path calculated in iGraph.
 *
 */

  class PathFlight : public FlightBehavior
  {
    public:
      /**
       *  @brief Constructor: set up Path Flight
       */
      PathFlight();

      /**
       *  @brief Constructor: set up Path Flight with a specific radius
       * @param radius the radius of the flight
       */
      PathFlight(float radius);

      /**
       *  This function adds an IGraph
       * @param systemGraph the graph of the system
       */
      void AddGraph(const IGraph *systemGraph);

      /**
       *  This function is called to update the drone/robot's position, based on the smart route
       * @param dt the time difference in Update function
       * @param pos the position
       * @param dir the direction
       */
      void FlightUpdate(float dt, std::vector<float>& pos, std::vector<float>& dir);

      /**
       *  This function is used whenever the drone's target needs to be set. This one is specifically used for the smart route.
       * @param pos the position
       * @param target the target destination
       * @param newGraph the graph
       */
      void SetFlightDetails(std::vector<float> pos,std::vector<float> target, const IGraph* newGraph);

      /**
       *  This function is used whenever the drone's target needs to be set, for flights that do not need the smart route Graph.
       * @param pos the position
       * @param target the target destination
       */
      void SetFlightDetails(std::vector<float> pos,std::vector<float> target);

      /**
       *  This function is used to calculate and return the distance from the drone/robot to the package from only x and z (y has to be ignored)
      * @param pos the position
       * @param target the target destination
       */
      float CalculateDistance(std::vector<float> pos,std::vector<float> target);

      /**
       *  This function should check whether the drone/robot should be aiming for the next node in the path
       * @param nextPosition the next position in the path
       * @param position the current position
       */
      bool CheckWhenToIncrementPathIndex(std::vector<float> &nextPosition, std::vector<float> position);

      /**
       *  This function updates the existing route, based on the new current position and destination
       * @param newPosition the new position
       */
      void SetNewCurRoute(std::vector<std::vector<float>> &newPosition);

      /**
        *  This function is used to set the current route
        * @param pos the position
        * @param target the target destination
        */
      void SetCurRoute(std::vector<float> pos, std::vector<float> target);

      /**
        *  This function is used to return the current route
        */
      std::vector<std::vector<float>> GetCurRoute();

    private:
      const IGraph *graph;
      std::vector<float> flightTarget;


      int curRouteNextIndex;
      int curRouteLength;
      float radius;
  };

} // namespace csci3081

#endif // PATH_FLIGHT_H

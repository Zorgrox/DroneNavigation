/**
 * @file package_scheduler.h
 */
#ifndef PACKAGE_SCHEDULER_H_
#define PACKAGE_SCHEDULER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include "drone.h"
#include <EntityProject/entity.h>
#include "package.h"
#include "customer.h"
#include "entity_base.h"
#include "robot.h"
#include "decorated_entity.h"
namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the helper class for scheduling deliveries in delivery simulation.
 *
 */

  class PackageScheduler
  {
  public:
    /**
   * @brief Constructor: set up a Package Scheduler
   */
    PackageScheduler(std::vector<IEntityObserver *> obs,
                     std::vector<Robot *> rob,
                     std::vector<Drone *> dron,
                     std::vector<int> dead_drones_ind,
                     std::vector<int> dead_robots_ind,
                     bool assignPackageToDron,
                     int robotsIdx,
                     int dronesIdx);

    /**
   *  Schedules the delivery of a package
   */
    std::vector<int> ScheduleDelivery(IEntity *package, IEntity *dest, const IGraph* graph);

  private:
    std::vector<IEntityObserver* > observers_;
    std::vector<Robot* > robots_;
    std::vector<Drone* > drones_;
    std::vector<int> dead_drones_indices;
    std::vector<int> dead_robots_indices;
    bool assignPackageToDrone;
    int robotsIndex;
    int dronesIndex;
  };

} // namespace csci3081

#endif // PACKAGE_SCHEDULER_H_

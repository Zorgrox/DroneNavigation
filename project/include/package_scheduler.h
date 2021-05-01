/**
 * @file package_scheduler.h
 */
#ifndef PACKAGE_SCHEDULER_H_
#define PACKAGE_SCHEDULER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "delivery_simulation.h"

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the helper class for scheduling deliveries in delivery simulation.
 *
 */

  class PackageScheduler : public csci3081::DeliverySimulation
  {
  public:
    /**
   * @brief Constructor: set up a Package Scheduler
   */
    PackageScheduler();

    /**
   *  Schedules the delivery of a package
   */
    void ScheduleDelivery(IEntity *package, IEntity *dest);
  };

} // namespace csci3081

#endif // PACKAGE_SCHEDULER_H_

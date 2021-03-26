/**
 * @file battery.h
 */
#ifndef BATTERY_H_
#define BATTERY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>
#include <string>

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the Battery class that stores the charge.
 *
 * This class will be used in the Drone class to represent the status of its battery.
 */

  class Battery
  {
  public:
    /**
   * @brief Constructor: set up a Battery with a specified maxCharge
   */
    Battery(float maxCharge);

    /**
   *  This function should return the max charge of the Battery
   */
    float GetMaxCharge() const;

    /**
   *  This function should return the current charge of the Battery
   */
    float GetCurrentCharge() const;

    /**
   *  This function should decrement the current charge by a constant amount
   */
    void DecrementCurrentCharge(float decrAmt);

    /**
   *  This function should return a boolean denoting whether the Battery has been completely drained
   */
    bool GetIsEmpty() const;

  private:
    float maxBatteryCharge;
    float currentCharge;
    bool isEmpty;
  };

} // namespace csci3081

#endif // BATTERY_H_

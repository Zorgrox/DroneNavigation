#include "gtest/gtest.h"
#include "battery.h"

#include <iostream>

namespace csci3081
{
  class BatteryTest : public ::testing::Test
  {
  protected:
    float maxBatteryCharge = 10.0;
  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  // Test Battery constructor and functions
  TEST_F(BatteryTest, BatteryConstructorTest)
  {
    Battery* battery = new Battery(maxBatteryCharge);
    ASSERT_FLOAT_EQ(battery->GetMaxCharge(), maxBatteryCharge);
    ASSERT_FLOAT_EQ(battery->GetCurrentCharge(), maxBatteryCharge);
    battery->DecrementCurrentCharge(1.0);
    ASSERT_FLOAT_EQ(battery->GetCurrentCharge(), maxBatteryCharge - 1.0);
  }
} // namespace csci3081

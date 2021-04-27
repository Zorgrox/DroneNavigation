#include "gtest/gtest.h"
#include "beeline_flight.h"

#include <iostream>

namespace csci3081
{
  class BeelineFlightTest : public ::testing::Test
  {
  protected:

  };

  TEST_F(BeelineFlightTest, BeelineFlightTestUpdate)
  {
    BeelineFlight* beeline = new BeelineFlight();
    std::vector<float> pos = { 1.0, 2.0, 3.0 };
    std::vector<float> target = {4.0, 5.0, 6.0};
    beeline->SetFlightDetails(pos, target);
    std::vector<float> direction = {7.0, 8.0, 9.0};
    std::vector<float> expected_direction = {7.0, 8.0, 9.0};
    std::vector<float> expected_pos = {1.0, 17.0, 3.0};
    float speedANDdt = 15.0;
    beeline->FlightUpdate(speedANDdt, pos, direction);
    ASSERT_NEAR(expected_pos[0], pos[0],0.1);
    ASSERT_NEAR(expected_pos[1], pos[1],0.1);
    ASSERT_NEAR(expected_pos[2], pos[2],0.1);
    ASSERT_NEAR(expected_direction[0], direction[0],0.1);
    ASSERT_NEAR(expected_direction[1], direction[1],0.1);
    ASSERT_NEAR(expected_direction[2], direction[2],0.1);

  }

}

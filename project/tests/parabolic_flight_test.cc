#include "gtest/gtest.h"
#include "parabolic_flight.h"

#include <iostream>

namespace csci3081
{
  class ParabolicFlightTest : public ::testing::Test
  {
  protected:

  };

  TEST_F(ParabolicFlightTest, ParabolicFlightTestUpdate)
  {
    ParabolicFlight* parabolic = new ParabolicFlight();
    std::vector<float> pos = { 1.0, 2.0, 3.0 };
    std::vector<float> target = {4.0, 5.0, 6.0};
    parabolic->SetFlightDetails(pos, target);
    std::vector<float> direction = {7.0, 8.0, 9.0};
    std::vector<float> expected_direction = {0.7071068286895752, 0.0, 0.7071068286895752};
    std::vector<float> expected_pos = {11.606602668762207, 2.0707106590270996, 13.606602668762207};
    float speedANDdt = 15.0;
    parabolic->FlightUpdate(speedANDdt, pos, direction);
    ASSERT_NEAR(expected_pos[0], pos[0],0.1);
    ASSERT_NEAR(expected_pos[1], pos[1],0.1);
    ASSERT_NEAR(expected_pos[2], pos[2],0.1);
    ASSERT_NEAR(expected_direction[0], direction[0],0.1);
    ASSERT_NEAR(expected_direction[1], direction[1],0.1);
    ASSERT_NEAR(expected_direction[2], direction[2],0.1);

  }

}

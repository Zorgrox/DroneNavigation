#include "gtest/gtest.h"
#include "path_flight.h"

#include <iostream>

namespace csci3081
{
  class SmartFlightTest : public ::testing::Test
  {
  protected:

  };

  TEST_F(SmartFlightTest, SmartFlightTestUpdate)
  {
    PathFlight* smart = new PathFlight();
    std::vector<std::vector<float>> testRoute = {{5.0,6.0,-6.0}, {10.0,8.0,-20.0}, {15.0,5.0,}};
    std::vector<float> pos = { 1.0, 2.0, 3.0 };
    std::vector<float> target = {4.0, 5.0, 6.0};
    //smart->SetFlightDetails(pos, target);
    smart->SetCurRouteTest(testRoute);
    std::vector<float> direction = {7.0, 8.0, 9.0};
    
    std::vector<float> expected_direction = {0.354, 0.236, -0.905};
    std::vector<float> expected_pos = {1.53, 2.35, 1.64};
    float speedANDdt = 1.5;
    smart->FlightUpdate(speedANDdt, pos, direction);
    //std::cout << direction[0] << " " << direction[1] << " " << direction[2] << std::endl;
    ASSERT_NEAR(expected_pos[0], pos[0],0.1);
    ASSERT_NEAR(expected_pos[1], pos[1],0.1);
    ASSERT_NEAR(expected_pos[2], pos[2],0.1);
    ASSERT_NEAR(expected_direction[0], direction[0],0.1);
    ASSERT_NEAR(expected_direction[1], direction[1],0.1);
    ASSERT_NEAR(expected_direction[2], direction[2],0.1);

  }

}

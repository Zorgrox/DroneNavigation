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

  TEST_F(BeelineFlightTest, SetFlightDetailsWithThreeArguments)
  {
    BeelineFlight* beeline = new BeelineFlight();
    std::vector<float> pos = { 1.0, 2.0, 3.0 };
    std::vector<float> target = {4.0, 5.0, 6.0};
    beeline->SetFlightDetails(pos, target, NULL);
    std::vector<std::vector<float>> routes = beeline->GetCurRoute();
    std::vector<std::vector<float>> expected_routes = {
    { 1,280, 3},
    { 1.1,280, 3.1},
    { 1.2,280, 3.2},
    { 1.3,280, 3.3},
    { 1.4,280, 3.4},
    { 1.5,280, 3.5},
    { 1.6,280, 3.6},
    { 1.7,280, 3.7},
    { 1.8,280, 3.8},
    { 1.9,280, 3.9},
    { 2,280, 4},
    { 2.1,280, 4.1},
    { 2.2,280, 4.2},
    { 2.3,280, 4.3},
    { 2.4,280, 4.4},
    { 2.5,280, 4.5},
    { 2.6,280, 4.6},
    { 2.7,280, 4.7},
    { 2.8,280, 4.8},
    { 2.9,280, 4.9},
    { 3,280, 5},
    { 3.1,280, 5.1},
    { 3.2,280, 5.2},
    { 3.3,280, 5.3},
    { 3.4,280, 5.4},
    { 3.5,280, 5.5},
    { 3.6,280, 5.6},
    { 3.7,280, 5.7},
    { 3.8,280, 5.8},
    { 3.9,280, 5.9},
    { 4,280, 6}
    };
    ASSERT_EQ(expected_routes.size(), routes.size());
    for(int i = 0; i<routes.size(); i++){
      ASSERT_NEAR(expected_routes[i][0], routes[i][0], 0.01);
      ASSERT_NEAR(expected_routes[i][1], routes[i][1], 0.01);
      ASSERT_NEAR(expected_routes[i][2], routes[i][2], 0.01);
    }
  }

  TEST_F(BeelineFlightTest, SetFlightDetailsWithTwoArguments)
  {
    BeelineFlight* beeline = new BeelineFlight();
    std::vector<float> pos = { 5.0, 6.0, 7.0 };
    std::vector<float> target = {8.0, 9.0, 10.0};
    beeline->SetFlightDetails(pos, target);
    std::vector<std::vector<float>> routes = beeline->GetCurRoute();
    std::vector<std::vector<float>> expected_routes = {
      { 5,280, 7},
      { 5.1,280, 7.1},
      { 5.2,280, 7.2},
      { 5.3,280, 7.3},
      { 5.4,280, 7.4},
      { 5.5,280, 7.5},
      { 5.6,280, 7.6},
      { 5.7,280, 7.7},
      { 5.8,280, 7.8},
      { 5.9,280, 7.9},
      { 6,280, 8},
      { 6.1,280, 8.1},
      { 6.2,280, 8.2},
      { 6.3,280, 8.3},
      { 6.4,280, 8.4},
      { 6.5,280, 8.5},
      { 6.6,280, 8.6},
      { 6.7,280, 8.7},
      { 6.8,280, 8.8},
      { 6.9,280, 8.9},
      { 7,280, 9},
      { 7.1,280, 9.1},
      { 7.2,280, 9.2},
      { 7.3,280, 9.3},
      { 7.4,280, 9.4},
      { 7.5,280, 9.5},
      { 7.6,280, 9.6},
      { 7.7,280, 9.7},
      { 7.8,280, 9.8},
      { 7.9,280, 9.9},
      { 8,280, 10},
        };
    ASSERT_EQ(expected_routes.size(), routes.size());
    for(int i = 0; i<routes.size(); i++){
      ASSERT_NEAR(expected_routes[i][0], routes[i][0], 0.01);
      ASSERT_NEAR(expected_routes[i][1], routes[i][1], 0.01);
      ASSERT_NEAR(expected_routes[i][2], routes[i][2], 0.01);
    }
  }

  TEST_F(BeelineFlightTest, CalculateDistance)
  {
    BeelineFlight* beeline = new BeelineFlight();
    std::vector<float> pos = { 2.0, 3.0, 5.0 };
    std::vector<float> target = {4.0, 5.0, 6.0};
    ASSERT_EQ(3.0, beeline->CalculateDistance(pos, target));
  }

  TEST_F(BeelineFlightTest, SetCurRoute)
  {
    BeelineFlight* beeline = new BeelineFlight();
    std::vector<float> pos = { 2.0, 3.0, 4.0 };
    std::vector<float> target = {8.0, 9.0, 10.0};
    beeline->SetCurRoute(pos, target);
    std::vector<std::vector<float>> routes = beeline->GetCurRoute();
    std::vector<std::vector<float>> expected_routes = {
      { 2,280, 4},
      { 2.2,280, 4.2},
      { 2.4,280, 4.4},
      { 2.6,280, 4.6},
      { 2.8,280, 4.8},
      { 3,280, 5},
      { 3.2,280, 5.2},
      { 3.4,280, 5.4},
      { 3.6,280, 5.6},
      { 3.8,280, 5.8},
      { 4,280, 6},
      { 4.2,280, 6.2},
      { 4.4,280, 6.4},
      { 4.6,280, 6.6},
      { 4.8,280, 6.8},
      { 5,280, 7},
      { 5.2,280, 7.2},
      { 5.4,280, 7.4},
      { 5.6,280, 7.6},
      { 5.8,280, 7.8},
      { 6,280, 8},
      { 6.2,280, 8.2},
      { 6.4,280, 8.4},
      { 6.6,280, 8.6},
      { 6.8,280, 8.8},
      { 7,280, 9},
      { 7.2,280, 9.2},
      { 7.4,280, 9.4},
      { 7.6,280, 9.6},
      { 7.8,280, 9.8},
      { 8,280, 10}
              };
    ASSERT_EQ(expected_routes.size(), routes.size());
    for(int i = 0; i<routes.size(); i++){
      ASSERT_NEAR(expected_routes[i][0], routes[i][0], 0.01);
      ASSERT_NEAR(expected_routes[i][1], routes[i][1], 0.01);
      ASSERT_NEAR(expected_routes[i][2], routes[i][2], 0.01);
    }
  }

  TEST_F(BeelineFlightTest, GetCurRoute)
  {
    BeelineFlight* beeline = new BeelineFlight();
    std::vector<float> pos = { 4.0, 5.0, 6.0 };
    std::vector<float> target = {8.0, 9.0, 10.0};
    beeline->SetCurRoute(pos, target);
    std::vector<std::vector<float>> routes = beeline->GetCurRoute();
    std::vector<std::vector<float>> expected_routes = {
      {4,280, 6},
      { 4.13333,280, 6.13333},
      { 4.26667,280, 6.26667},
      { 4.4,280, 6.4},
      { 4.53333,280, 6.53333},
      { 4.66667,280, 6.66667},
      { 4.8,280, 6.8},
      { 4.93333,280, 6.93333},
      { 5.06667,280, 7.06667},
      { 5.2,280, 7.2},
      { 5.33333,280, 7.33333},
      { 5.46667,280, 7.46667},
      { 5.6,280, 7.6},
      { 5.73333,280, 7.73333},
      { 5.86667,280, 7.86667},
      { 6,280, 8},
      { 6.13333,280, 8.13333},
      { 6.26667,280, 8.26667},
      { 6.4,280, 8.4},
      { 6.53333,280, 8.53333},
      { 6.66667,280, 8.66667},
      { 6.8,280, 8.8},
      { 6.93333,280, 8.93333},
      { 7.06667,280, 9.06667},
      { 7.2,280, 9.2},
      { 7.33333,280, 9.33333},
      { 7.46667,280, 9.46667},
      { 7.6,280, 9.6},
      { 7.73333,280, 9.73333},
      { 7.86667,280, 9.86667},
      { 8,280, 10},
              };
    ASSERT_EQ(expected_routes.size(), routes.size());
    for(int i = 0; i<routes.size(); i++){
      ASSERT_NEAR(expected_routes[i][0], routes[i][0], 0.01);
      ASSERT_NEAR(expected_routes[i][1], routes[i][1], 0.01);
      ASSERT_NEAR(expected_routes[i][2], routes[i][2], 0.01);
    }
  }
}

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

  TEST_F(ParabolicFlightTest, SetFlightDetailsWithThreeArguments)
  {
    ParabolicFlight* parabolic = new ParabolicFlight();
    std::vector<float> pos = { 1.0, 2.0, 3.0 };
    std::vector<float> target = {4.0, 5.0, 6.0};
    parabolic->SetFlightDetails(pos, target, NULL);
    std::vector<std::vector<float>> routes = parabolic->GetCurRoute();
    std::vector<std::vector<float>> expected_routes = {
        { 1,2.07071, 3},
        { 1.1,2.49497, 3.1},
        { 1.2,2.49497, 3.2},
        { 1.3,2.49497, 3.3},
        { 1.4,2.49497, 3.4},
        { 1.5,2.49497, 3.5},
        { 1.6,2.49497, 3.6},
        { 1.7,2.49497, 3.7},
        { 1.8,2.6364, 3.8},
        { 1.9,2.6364, 3.9},
        { 2,2.6364, 4},
        { 2.1,2.6364, 4.1},
        { 2.2,2.6364, 4.2},
        { 2.3,2.6364, 4.3},
        { 2.4,2.6364, 4.4},
        { 2.5,2.6364, 4.5},
        { 2.6,2.6364, 4.6},
        { 2.7,2.6364, 4.7},
        { 2.8,2.6364, 4.8},
        { 2.9,2.6364, 4.9},
        { 3,2.6364, 5},
        { 3.1,2.6364, 5.1},
        { 3.2,2.6364, 5.2},
        { 3.3,2.49497, 5.3},
        { 3.4,2.49497, 5.4},
        { 3.5,2.49497, 5.5},
        { 3.6,2.49497, 5.6},
        { 3.7,2.49497, 5.7},
        { 3.8,2.49497, 5.8},
        { 3.9,2.49497, 5.9},
        { 4,2.07071, 6}
    };
    ASSERT_EQ(expected_routes.size(), routes.size());
    for(int i = 0; i<routes.size(); i++){
      ASSERT_NEAR(expected_routes[i][0], routes[i][0], 0.01);
      ASSERT_NEAR(expected_routes[i][1], routes[i][1], 0.01);
      ASSERT_NEAR(expected_routes[i][2], routes[i][2], 0.01);
    }
  }

  TEST_F(ParabolicFlightTest, SetFlightDetailsWithTwoArguments)
  {
    ParabolicFlight* parabolic = new ParabolicFlight();
    std::vector<float> pos = { 5.0, 6.0, 7.0 };
    std::vector<float> target = {8.0, 9.0, 10.0};
    parabolic->SetFlightDetails(pos, target);
    std::vector<std::vector<float>> routes = parabolic->GetCurRoute();
    std::vector<std::vector<float>> expected_routes = {
      { 5,6.07071, 7},
      { 5.1,6.49497, 7.1},
      { 5.2,6.49497, 7.2},
      { 5.3,6.49497, 7.3},
      { 5.4,6.49497, 7.4},
      { 5.5,6.49497, 7.5},
      { 5.6,6.49497, 7.6},
      { 5.7,6.49497, 7.7},
      { 5.8,6.6364, 7.8},
      { 5.9,6.6364, 7.9},
      { 6,6.6364, 8},
      { 6.1,6.6364, 8.1},
      { 6.2,6.6364, 8.2},
      { 6.3,6.6364, 8.3},
      { 6.4,6.6364, 8.4},
      { 6.5,6.6364, 8.5},
      { 6.6,6.6364, 8.6},
      { 6.7,6.6364, 8.7},
      { 6.8,6.6364, 8.8},
      { 6.9,6.6364, 8.9},
      { 7,6.6364, 9},
      { 7.1,6.6364, 9.1},
      { 7.2,6.6364, 9.2},
      { 7.3,6.49497, 9.3},
      { 7.4,6.49497, 9.4},
      { 7.5,6.49497, 9.5},
      { 7.6,6.49497, 9.6},
      { 7.7,6.49497, 9.7},
      { 7.8,6.49497, 9.8},
      { 7.9,6.49497, 9.9},
      { 8,6.07071, 10}

        };
    ASSERT_EQ(expected_routes.size(), routes.size());
    for(int i = 0; i<routes.size(); i++){
      ASSERT_NEAR(expected_routes[i][0], routes[i][0], 0.01);
      ASSERT_NEAR(expected_routes[i][1], routes[i][1], 0.01);
      ASSERT_NEAR(expected_routes[i][2], routes[i][2], 0.01);
    }
  }

  TEST_F(ParabolicFlightTest, CalculateDistance)
  {
    ParabolicFlight* parabolic = new ParabolicFlight();
    std::vector<float> pos = { 5.0, 6.0, 7.0 };
    std::vector<float> target = {2.0, 8.0, 3.0};
    ASSERT_EQ(5.0, parabolic->CalculateDistance(pos, target));
  }

  TEST_F(ParabolicFlightTest, SetCurRoute)
  {
    ParabolicFlight* parabolic = new ParabolicFlight();
    std::vector<float> pos = { 2.0, 3.0, 4.0 };
    std::vector<float> target = {8.0, 9.0, 10.0};
    parabolic->SetCurRoute(pos, target);
    std::vector<std::vector<float>> routes = parabolic->GetCurRoute();
    std::vector<std::vector<float>> expected_routes = {
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4},
      { 2,0, 4}

              };
    ASSERT_EQ(expected_routes.size(), routes.size());
    for(int i = 0; i<routes.size(); i++){
      ASSERT_NEAR(expected_routes[i][0], routes[i][0], 0.01);
      ASSERT_NEAR(expected_routes[i][1], routes[i][1], 0.01);
      ASSERT_NEAR(expected_routes[i][2], routes[i][2], 0.01);
    }
  }

  TEST_F(ParabolicFlightTest, GetCurRoute)
  {
    ParabolicFlight* parabolic = new ParabolicFlight();
    std::vector<float> pos = { 4.0, 5.0, 6.0 };
    std::vector<float> target = {8.0, 9.0, 10.0};
    parabolic->SetCurRoute(pos, target);
    std::vector<std::vector<float>> routes = parabolic->GetCurRoute();
    std::vector<std::vector<float>> expected_routes = {
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6},
      { 4,0, 6}
              };
    ASSERT_EQ(expected_routes.size(), routes.size());
    for(int i = 0; i<routes.size(); i++){
      ASSERT_NEAR(expected_routes[i][0], routes[i][0], 0.01);
      ASSERT_NEAR(expected_routes[i][1], routes[i][1], 0.01);
      ASSERT_NEAR(expected_routes[i][2], routes[i][2], 0.01);
    }
  }
}

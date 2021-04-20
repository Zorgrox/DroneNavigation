#include "gtest/gtest.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector2d.h"
#include "robot.h"
#include "json_helper.h"

#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>

#include <iostream>

namespace csci3081
{
  class RobotTest : public ::testing::Test
  {
  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  // Test Robot constructor and that its values are correctly set
  TEST_F(RobotTest, RobotConstructorTest)
  {
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "robot");
    JsonHelper::AddStringToJsonObject(obj, "name", "robot");
    std::vector<float> position_to_add;
    position_to_add.push_back(2);
    position_to_add.push_back(5);
    position_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add;
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 30);

    Robot* robot = new Robot(obj);

    int expectedRobotId = 0;
    ASSERT_EQ(robot->GetId(), expectedRobotId);

    std::string expectedRobotName = "robot";
    ASSERT_EQ(robot->GetName(), expectedRobotName);

    std::vector<float> expectedRobotPos{2, 5, 0};
    ASSERT_EQ(robot->GetPosition(), expectedRobotPos);
    std::vector<float> expectedRobotDirection{0, 0, 1};
    ASSERT_EQ(robot->GetDirection(), expectedRobotDirection);

    float expectedRobotRadius = 1.0;
    ASSERT_EQ(robot->GetRadius(), expectedRobotRadius);

    int expectedRobotVersion = 0;
    ASSERT_EQ(robot->GetVersion(), expectedRobotVersion);

    bool expectedRobotDynamic = true;
    ASSERT_EQ(robot->IsDynamic(), expectedRobotDynamic);

    robot->SetIsCarryingPackage(false);
    ASSERT_EQ(robot->GetIsCarryingPackage(), false);

    robot->SetOnTheWayToDropOffPackage(true);
    ASSERT_EQ(robot->GetOnTheWayToDropOffPackage(), true);

    robot->SetOnTheWayToPickUpPackage(true);
    ASSERT_EQ(robot->GetOnTheWayToPickUpPackage(), true);
  }

  TEST_F(RobotTest, RobotMovementTest)
  {
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "robot");
    JsonHelper::AddStringToJsonObject(obj, "name", "robot");
    std::vector<float> position_to_add;
    position_to_add.push_back(2);
    position_to_add.push_back(5);
    position_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add;
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 30);

    Robot *robot = new Robot(obj);

    std::vector<float> new_position_to_add;
    new_position_to_add.push_back(2);
    new_position_to_add.push_back(5);
    new_position_to_add.push_back(1);

    std::vector<float> expectedDirection;
    expectedDirection.push_back(0);
    expectedDirection.push_back(0);
    expectedDirection.push_back(1);

    robot->CalculateAndUpdateRobotDirection(new_position_to_add);
    ASSERT_EQ(robot->GetDirection(), expectedDirection);

  }

} // namespace csci3081

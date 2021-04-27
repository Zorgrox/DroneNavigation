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
    JsonHelper::AddFloatToJsonObject(obj, "battery_capacity", 20.0);

    Robot* robot = new Robot(obj);

    int expectedRobotId = 0;
    ASSERT_EQ(robot->GetId(), expectedRobotId);

    int newRobotId = 2;
    robot->SetId(2);
    ASSERT_EQ(robot->GetId(), newRobotId);

    float battery_capacity = 20.0;
    const Battery* battery = robot->GetBattery();
    ASSERT_EQ(battery->GetMaxCharge(), battery_capacity);

    robot->UpdateBatteryCharge(10.0);
    ASSERT_EQ(battery->GetCurrentCharge(), battery_capacity - 10.0);

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

  // Test the robot movement update functions
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
    std::vector<IEntityObserver*> observers;

    robot->UpdateRobotPosition(1.0, observers);

    std::vector<float> another_position;
    another_position.push_back(2);
    another_position.push_back(5);
    another_position.push_back(30);
    ASSERT_EQ(robot->GetPosition(), another_position);

    std::vector<float> new_position_to_add;
    new_position_to_add.push_back(2);
    new_position_to_add.push_back(5);
    new_position_to_add.push_back(31);

    std::vector<float> expectedDirection;
    expectedDirection.push_back(0);
    expectedDirection.push_back(0);
    expectedDirection.push_back(1);

    robot->CalculateAndUpdateRobotDirection(new_position_to_add);
    ASSERT_EQ(robot->GetDirection(), expectedDirection);

    // test the route functions
    std::vector<std::vector<float>> hardcodedRoute;
    std::vector<float> first_node;
    first_node.push_back(3.2);
    first_node.push_back(5);
    first_node.push_back(31);
    hardcodedRoute.push_back(new_position_to_add);
    hardcodedRoute.push_back(first_node);

    robot->SetNewCurRoute(hardcodedRoute);
    ASSERT_EQ(robot->GetCurRouteLength(), 2);
    ASSERT_EQ(robot->GetCurRouteNextIndex(), 1);
    ASSERT_EQ(robot->CheckWhenToIncrementPathIndex(first_node), false);
    robot->IncrementCurRouteNextIndex();

    ASSERT_EQ(robot->GetCurRouteNextIndex(), 2);
  }

  // Test the package queue system in the robot
  TEST_F(RobotTest, RobotPackageTest)
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

    picojson::object obj1 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj1, "type", "package");
    JsonHelper::AddStringToJsonObject(obj1, "name", "package");
    std::vector<float> position_to_add1;
    position_to_add1.push_back(2);
    position_to_add1.push_back(4);
    position_to_add1.push_back(5);
    JsonHelper::AddStdFloatVectorToJsonObject(obj1, "position", position_to_add1);
    std::vector<float> direction_to_add1;
    direction_to_add1.push_back(0);
    direction_to_add1.push_back(0);
    direction_to_add1.push_back(1);
    JsonHelper::AddStdFloatVectorToJsonObject(obj1, "direction", direction_to_add1);
    JsonHelper::AddFloatToJsonObject(obj1, "radius", 1.0);

    Package *package = new Package(obj1);

    robot->AddAssignedPackage(*package);
    ASSERT_EQ(robot->GetNumAssignedPackages(), 1);

    robot->SetIsCarryingPackage(true);
    ASSERT_EQ(robot->GetIsCarryingPackage(), true);

    robot->UpdateCurPackage();
    ASSERT_EQ(robot->GetCurPackage(), package);

    std::vector<Package*> assignedPackages;
    assignedPackages.push_back(package);
    ASSERT_EQ(robot->GetRemainingAssignedPackages(), assignedPackages);

    robot->DropOffPackage();
    ASSERT_EQ(robot->GetIsCarryingPackage(), false);

    robot->PickUpPackage();
    ASSERT_EQ(robot->GetIsCarryingPackage(), true);
  }

} // namespace csci3081

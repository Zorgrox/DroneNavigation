#include "gtest/gtest.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "drone.h"
#include "json_helper.h"

#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>

#include <EntityProject/graph.h>

#include <iostream>

namespace csci3081
{
  class DroneTest : public ::testing::Test
  {
  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  // Test Drone constructor and that its values are correctly set
  TEST_F(DroneTest, ConstructorTest)
  {
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj, "name", "drone");
    std::vector<float> position_to_add;
    position_to_add.push_back(2);
    position_to_add.push_back(4);
    position_to_add.push_back(5);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add;
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 30);
    JsonHelper::AddFloatToJsonObject(obj, "battery_capacity", 20.0);

    Drone* drone = new Drone(obj);

    int newDroneId = 2;
    drone->SetId(newDroneId);
    ASSERT_EQ(drone->GetId(), newDroneId);

    float battery_capacity = 20.0;
    const Battery* battery = drone->GetBattery();
    ASSERT_EQ(battery->GetMaxCharge(), battery_capacity);

    drone->UpdateBatteryCharge(10.0);
    ASSERT_EQ(battery->GetCurrentCharge(), battery_capacity - 10.0);

    std::string expectedDroneName = "drone";
    ASSERT_EQ(drone->GetName(), expectedDroneName);

    std::vector<float> expectedDronePos{2, 4, 5};
    ASSERT_EQ(drone->GetPosition(), expectedDronePos);
    std::vector<float> expectedDroneDirection{0, 0, 1};
    ASSERT_EQ(drone->GetDirection(), expectedDroneDirection);

    ASSERT_EQ(drone->GetSpeed(), 30);

    float expectedDroneRadius = 1.0;
    ASSERT_EQ(drone->GetRadius(), expectedDroneRadius);

    int expectedDroneVersion = 0;
    ASSERT_EQ(drone->GetVersion(), expectedDroneVersion);

    bool expectedDroneDynamic = true;
    ASSERT_EQ(drone->IsDynamic(), expectedDroneDynamic);

    drone->SetIsCarryingPackage(false);
    ASSERT_EQ(drone->GetIsCarryingPackage(), false);

    drone->SetOnTheWayToDropOffPackage(true);
    ASSERT_EQ(drone->GetOnTheWayToDropOffPackage(), true);

    drone->SetOnTheWayToPickUpPackage(true);
    ASSERT_EQ(drone->GetOnTheWayToPickUpPackage(), true);
  }

  // Test the drone movement and update functions, according to the smart path strategy
  TEST_F(DroneTest, DroneMovementTest)
  {
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj, "name", "drone");
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
    JsonHelper::AddStringToJsonObject(obj, "path", "beeline");

    Drone* drone = new Drone(obj);
    std::vector<IEntityObserver *> observers;

    drone->SetFlightStrategyIndex(1, false); // smart path that does not change
    drone->ChooseFlightStrategy();

    drone->UpdateDronePosition(1.0, observers);

    std::vector<float> another_position;
    another_position.push_back(2);
    another_position.push_back(35);
    another_position.push_back(0);

    std::cout << "This is the direction: " << drone->GetDirection().at(0) << ", " << drone->GetDirection().at(1) << ", " << drone->GetDirection().at(2) << std::endl;
    ASSERT_EQ(drone->GetPosition(), another_position);

    std::vector<float> new_position_to_add;
    new_position_to_add.push_back(2);
    new_position_to_add.push_back(35);
    new_position_to_add.push_back(30);

    std::vector<float> expectedDirection;
    expectedDirection.push_back(0);
    expectedDirection.push_back(0);
    expectedDirection.push_back(1);

    drone->CalculateAndUpdateDroneDirection(new_position_to_add);
    ASSERT_EQ(drone->GetDirection(), expectedDirection);

    // test the route functions
    std::vector<std::vector<float>> hardcodedRoute;
    std::vector<float> first_node;
    first_node.push_back(3.2);
    first_node.push_back(5);
    first_node.push_back(31);
    hardcodedRoute.push_back(new_position_to_add);
    hardcodedRoute.push_back(first_node);

    drone->SetNewCurRoute(hardcodedRoute);
    ASSERT_EQ(drone->GetCurRouteLength(), 2);
    ASSERT_EQ(drone->GetCurRouteNextIndex(), 1);
    drone->IncrementCurRouteNextIndex();

    ASSERT_EQ(drone->GetCurRouteNextIndex(), 2);
  }

  // Test the drone package queue system
  TEST_F(DroneTest, DronePackageTest)
  {
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj, "name", "drone");
    std::vector<float> position_to_add;
    position_to_add.push_back(2);
    position_to_add.push_back(4);
    position_to_add.push_back(5);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add;
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 30);

    Drone *drone = new Drone(obj);

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

    drone->AddAssignedPackage(*package);
    ASSERT_EQ(drone->GetNumAssignedPackages(), 1);

    drone->SetIsCarryingPackage(true);
    ASSERT_EQ(drone->GetIsCarryingPackage(), true);

    drone->UpdateCurPackage();
    ASSERT_EQ(drone->GetCurPackage(), package);

    std::vector<Package *> assignedPackages;
    assignedPackages.push_back(package);
    ASSERT_EQ(drone->GetRemainingAssignedPackages(), assignedPackages);

    drone->DropOffPackage();
    ASSERT_EQ(drone->GetIsCarryingPackage(), false);

    drone->PickUpPackage();
    ASSERT_EQ(drone->GetIsCarryingPackage(), true);
  }

} // namespace csci3081

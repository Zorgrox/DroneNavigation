#include "gtest/gtest.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "drone.h"
#include "decorated_drone.h"
#include "json_helper.h"

#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>

#include <EntityProject/osm_graph_parser.h>
#include <EntityProject/graph.h>

#include <iostream>

namespace csci3081
{
  class DecoratedDroneTest : public ::testing::Test
  {
  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  // Test Decorated Drone constructor and that its values are correctly set
  TEST_F(DecoratedDroneTest, ConstructorTest)
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

    Drone *drone = new Drone(obj);

    DecoratedDrone *decorated_drone = new DecoratedDrone(drone);

    int newDroneId = 2;
    decorated_drone->SetId(newDroneId);
    ASSERT_EQ(decorated_drone->GetId(), newDroneId);

    float battery_capacity = 20.0;
    const Battery *battery = decorated_drone->GetBattery();
    ASSERT_EQ(battery->GetMaxCharge(), battery_capacity);

    decorated_drone->UpdateBatteryCharge(10.0);
    ASSERT_EQ(battery->GetCurrentCharge(), battery_capacity - 10.0);

    std::string expectedDroneName = "drone";
    ASSERT_EQ(decorated_drone->GetName(), expectedDroneName);

    std::vector<float> expectedDronePos{2, 4, 5};
    ASSERT_EQ(decorated_drone->GetPosition(), expectedDronePos);
    std::vector<float> expectedDroneDirection{0, 0, 1};
    ASSERT_EQ(decorated_drone->GetDirection(), expectedDroneDirection);

    ASSERT_EQ(decorated_drone->GetSpeed(), 30);

    float expectedDroneRadius = 1.0;
    ASSERT_EQ(decorated_drone->GetRadius(), expectedDroneRadius);

    int expectedDroneVersion = 0;
    ASSERT_EQ(decorated_drone->GetVersion(), expectedDroneVersion);

    bool expectedDroneDynamic = true;
    ASSERT_EQ(decorated_drone->IsDynamic(), expectedDroneDynamic);

    drone->SetIsCarryingPackage(false);
    ASSERT_EQ(decorated_drone->GetIsCarryingPackage(), false);

    drone->SetOnTheWayToDropOffPackage(true);
    ASSERT_EQ(decorated_drone->GetOnTheWayToDropOffPackage(), true);

    drone->SetOnTheWayToPickUpPackage(true);
    ASSERT_EQ(decorated_drone->GetOnTheWayToPickUpPackage(), true);
  }

  // Test the drone movement and update functions, according to the smart path strategy
  TEST_F(DecoratedDroneTest, DecoratedDroneMovementTest)
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

    Drone *drone = new Drone(obj);
    DecoratedDrone *decorated_drone = new DecoratedDrone(drone);
    std::vector<IEntityObserver *> observers;

    decorated_drone->SetFlightStrategyIndex(1, false); // smart path that does not change
    decorated_drone->ChooseFlightStrategy();

    decorated_drone->UpdateDronePosition(1.0, observers);

    std::vector<float> another_position;
    another_position.push_back(2);
    another_position.push_back(35);
    another_position.push_back(0);

    std::cout << "This is the direction: " << decorated_drone->GetDirection().at(0) << ", " << decorated_drone->GetDirection().at(1) << ", " << decorated_drone->GetDirection().at(2) << std::endl;
    ASSERT_EQ(decorated_drone->GetPosition(), another_position);

    std::vector<float> new_position_to_add;
    new_position_to_add.push_back(2);
    new_position_to_add.push_back(35);
    new_position_to_add.push_back(30);

    std::vector<float> expectedDirection;
    expectedDirection.push_back(0);
    expectedDirection.push_back(0);
    expectedDirection.push_back(1);

    decorated_drone->CalculateAndUpdateDroneDirection(new_position_to_add);
    ASSERT_EQ(decorated_drone->GetDirection(), expectedDirection);

    // test the route functions
    std::vector<std::vector<float>> hardcodedRoute;
    std::vector<float> first_node;
    first_node.push_back(3.2);
    first_node.push_back(5);
    first_node.push_back(31);
    hardcodedRoute.push_back(new_position_to_add);
    hardcodedRoute.push_back(first_node);

    decorated_drone->SetNewCurRoute(hardcodedRoute);
    ASSERT_EQ(decorated_drone->GetCurRouteLength(), 2);
    ASSERT_EQ(decorated_drone->GetCurRouteNextIndex(), 1);
    decorated_drone->IncrementCurRouteNextIndex();

    ASSERT_EQ(decorated_drone->GetCurRouteNextIndex(), 2);
  }

  // Test the drone package queue system
  TEST_F(DecoratedDroneTest, DronePackageTest)
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
    DecoratedDrone *decorated_drone = new DecoratedDrone(drone);

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
    std::cout << "Created json helper object" << std::endl;

    Package *package = new Package(obj1);

    decorated_drone->AddAssignedPackage(*package);
    ASSERT_EQ(decorated_drone->GetNumAssignedPackages(), 1);
    std::cout << "Added assigned package" << std::endl;

    decorated_drone->SetIsCarryingPackage(true);
    ASSERT_EQ(decorated_drone->GetIsCarryingPackage(), true);

    decorated_drone->UpdateCurPackage();
    ASSERT_EQ(decorated_drone->GetCurPackage(), package);

    std::vector<Package *> assignedPackages;
    assignedPackages.push_back(package);
    ASSERT_EQ(decorated_drone->GetRemainingAssignedPackages(), assignedPackages);

    decorated_drone->DropOffPackage();
    ASSERT_EQ(decorated_drone->GetIsCarryingPackage(), false);

    decorated_drone->PickUpPackage();
    ASSERT_EQ(decorated_drone->GetIsCarryingPackage(), true);
  }

  TEST_F(DecoratedDroneTest, ColorUpdateTest) {
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
    JsonHelper::AddFloatToJsonObject(obj, "battery_capacity", 15.0);

    Drone *drone = new Drone(obj);
    DecoratedDrone *decorated_drone = new DecoratedDrone(drone);

    std::vector<IEntityObserver *> observers_;
    float dt = 1.0;

    decorated_drone->SetOnTheWayToDropOffPackage(false);
    decorated_drone->SetOnTheWayToPickUpPackage(false);

    // make this test dependent on the battery life, since that's what the color depends on

    entity_project::OSMGraphParser parser;
    const IGraph *systemGraph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
    // Note: first test the color when the battery is full
    decorated_drone->Update(systemGraph, observers_, dt);
    picojson::object &drone_obj = const_cast<picojson::object &>(decorated_drone->GetDetails());
    float actual_color = (float) JsonHelper::GetDouble(drone_obj, "color");
    ASSERT_EQ(actual_color, 872809);

    // Then test the color when the battery is at 14/15
    float subtract_battery_capacity = 1.0;
    decorated_drone->UpdateBatteryCharge(subtract_battery_capacity);
    decorated_drone->Update(systemGraph, observers_, dt);
    actual_color = (float)JsonHelper::GetDouble(drone_obj, "color");
    ASSERT_EQ(actual_color, 874011);

    // Then test the color when the battery is at 2/15
    decorated_drone->UpdateBatteryCharge(12.0);
    decorated_drone->Update(systemGraph, observers_, dt);
    actual_color = (float)JsonHelper::GetDouble(drone_obj, "color");
    ASSERT_EQ(actual_color, 388708);

    // Then test the color when the battery is at zero
    decorated_drone->UpdateBatteryCharge(2.0);
    decorated_drone->Update(systemGraph, observers_, dt);
    actual_color = (float)JsonHelper::GetDouble(drone_obj, "color");
    ASSERT_EQ(actual_color, 268705);
  }

} // namespace csci3081

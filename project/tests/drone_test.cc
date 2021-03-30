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

#include <iostream>

namespace csci3081
{
  class DroneTest : public ::testing::Test
  {
  protected:
    virtual void SetUp()
    {
      system = dynamic_cast<IDeliverySystem *>(GetEntitySystem("default"));
    }
    virtual void TearDown() {}

    IDeliverySystem *system;
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

    IEntity *droneEntity = system->CreateEntity(obj);
    Drone *drone = dynamic_cast<Drone *>(droneEntity);

    int expectedDroneId = 0;
    ASSERT_EQ(drone->GetId(), expectedDroneId);

    std::string expectedDroneName = "drone";
    ASSERT_EQ(drone->GetName(), expectedDroneName);

    std::vector<float> expectedDronePos{2, 4, 5};
    ASSERT_EQ(drone->GetPosition(), expectedDronePos);
    std::vector<float> expectedDroneDirection{0, 0, 1};
    ASSERT_EQ(drone->GetDirection(), expectedDroneDirection);

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

  TEST_F(DroneTest, DroneMovementTest)
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

    IEntity *droneEntity = system->CreateEntity(obj);
    Drone *drone = dynamic_cast<Drone *>(droneEntity);
	//Drone *drone2 = dynamic_cast<Drone *> (system->CreateEntity(obj));
	
    std::vector<float> new_position_to_add;
    new_position_to_add.push_back(2);
    new_position_to_add.push_back(4);
    new_position_to_add.push_back(6);

    std::vector<float> expectedDirection;
    expectedDirection.push_back(0);
    expectedDirection.push_back(0);
    expectedDirection.push_back(1);

    drone->CalculateAndUpdateDroneDirection(new_position_to_add);
    ASSERT_EQ(drone->GetDirection(), expectedDirection);
	//ASSERT_EQ(drone->GetId(), drone2->GetId());

  }

} // namespace csci3081

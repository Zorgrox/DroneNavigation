#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class FactoryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

// Original test to create the drone
TEST_F(FactoryTest, DroneCreated) {
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
  IEntity *entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());
  }

  // Test that the composite factory creates the right type of entity
  TEST_F(FactoryTest, CompositeFactoryTest) {
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
    IEntity *entity = system->CreateEntity(obj);

    CompositeFactory *compositeFactory_ = new CompositeFactory();
    IEntity* drone = compositeFactory_->CreateEntity(obj);

    ASSERT_EQ(drone->GetId(), entity->GetId());

  }
}  // namespace csci3081

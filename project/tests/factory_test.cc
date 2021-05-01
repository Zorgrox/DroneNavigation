#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone_factory.h"
#include "robot_factory.h"
#include "package_factory.h"
#include "customer_factory.h"

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
  JsonHelper::AddFloatToJsonObject(obj, "color", 0x990000);
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

  // Test the different factories independently of IDeliverySystem and of CompositeFactory
  TEST_F(FactoryTest, IndependentFactoryTests)
  {
    DroneFactory *drone_factory = new DroneFactory();
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
    drone_factory->CreateEntity(obj);
    IEntity *drone = drone_factory->CreateEntity(obj);
    ASSERT_EQ(drone->GetName(), "drone");

    RobotFactory *robot_factory = new RobotFactory();
    picojson::object robot_obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(robot_obj, "type", "robot");
    JsonHelper::AddStringToJsonObject(robot_obj, "name", "robot");
    JsonHelper::AddStdFloatVectorToJsonObject(robot_obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(robot_obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(robot_obj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(robot_obj, "speed", 30);
    robot_factory->CreateEntity(robot_obj);
    IEntity *robot = robot_factory->CreateEntity(robot_obj);
    ASSERT_EQ(robot->GetName(), "robot");

    CustomerFactory *customer_factory = new CustomerFactory();
    picojson::object customer_obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(customer_obj, "type", "customer");
    JsonHelper::AddStringToJsonObject(customer_obj, "name", "customer");
    JsonHelper::AddStdFloatVectorToJsonObject(customer_obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(customer_obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(customer_obj, "radius", 1.0);
    customer_factory->CreateEntity(customer_obj);
    IEntity *customer = customer_factory->CreateEntity(customer_obj);
    ASSERT_EQ(customer->GetName(), "customer");

    PackageFactory *package_factory = new PackageFactory();
    picojson::object package_obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(package_obj, "type", "package");
    JsonHelper::AddStringToJsonObject(package_obj, "name", "package");
    JsonHelper::AddStdFloatVectorToJsonObject(package_obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(package_obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(package_obj, "radius", 1.0);
    package_factory->CreateEntity(package_obj);
    IEntity *package = package_factory->CreateEntity(package_obj);
    ASSERT_EQ(package->GetName(), "package");

  }


}  // namespace csci3081

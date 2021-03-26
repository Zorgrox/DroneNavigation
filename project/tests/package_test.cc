#include "gtest/gtest.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "package.h"
#include "json_helper.h"

#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>

#include <iostream>

namespace csci3081
{
  class PackageTest : public ::testing::Test
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

  // Test Package constructor and that its values are correctly set
  TEST_F(PackageTest, PackageConstructorTest)
  {
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "package");
    JsonHelper::AddStringToJsonObject(obj, "name", "package");
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
    IEntity *packageEntity = system->CreateEntity(obj);
    Package *package = dynamic_cast<Package *>(packageEntity);

    int expectedPackageId = 2;
    ASSERT_EQ(package->GetId(), expectedPackageId);

    std::string expectedPackageName = "package";
    ASSERT_EQ(package->GetName(), expectedPackageName);

    std::vector<float> expectedPackagePos{2, 4, 5};
    ASSERT_EQ(package->GetPosition(), expectedPackagePos);

    std::vector<float> expectedPackageDirection{0, 0, 1};
    ASSERT_EQ(package->GetDirection(), expectedPackageDirection);

    float expectedPackageRadius = 1.0;
    ASSERT_FLOAT_EQ(package->GetRadius(), expectedPackageRadius);

    int expectedPackageVersion = 0;
    ASSERT_EQ(package->GetVersion(), expectedPackageVersion);

    bool expectedPackageDynamic = true;
    ASSERT_EQ(package->IsDynamic(), expectedPackageDynamic);

    float expectedWeight = 0.0;
    ASSERT_FLOAT_EQ(package->GetWeight(), expectedWeight);

  }
} // namespace csci3081

#include "gtest/gtest.h"
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "customer.h"
#include "json_helper.h"

#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>

#include <iostream>

namespace csci3081
{
  class CustomerTest : public ::testing::Test
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

  // Test Customer constructor and that its values are correctly set
  TEST_F(CustomerTest, CustomerConstructorTest)
  {
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    JsonHelper::AddStringToJsonObject(obj, "name", "customer");
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
    IEntity *customerEntity = system->CreateEntity(obj);
    Customer *customer = dynamic_cast<Customer *>(customerEntity);

    int expectedCustomerId = 0;
    int actualCustomerId = customer->GetId();
    ASSERT_EQ(customer->GetId(), expectedCustomerId);

    std::string expectedCustomerName = "customer";
    ASSERT_EQ(customer->GetName(), expectedCustomerName);

    std::vector<float> expectedCustomerPos{2, 4, 5};
    // ASSERT_FLOAT_EQ(customer->GetPosition().at(0), expectedCustomerPos.at(0));
    ASSERT_EQ(customer->GetPosition(), expectedCustomerPos);

    std::vector<float> expectedCustomerDirection{0, 0, 1};
    ASSERT_EQ(customer->GetDirection(), expectedCustomerDirection);

    float expectedCustomerRadius = 1.0;
    ASSERT_EQ(customer->GetRadius(), expectedCustomerRadius);

    int expectedCustomerVersion = 0;
    ASSERT_EQ(customer->GetVersion(), expectedCustomerVersion);

    bool expectedCustomerDynamic = false;
    ASSERT_EQ(customer->IsDynamic(), expectedCustomerDynamic);
  }
} // namespace csci3081

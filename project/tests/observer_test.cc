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
#include <EntityProject/entity_console_logger.h>

#include <iostream>

namespace csci3081
{
  class ObserverTest : public ::testing::Test
  {

    // Resource used to capture stdout with Google Test: https://stackoverflow.com/questions/3803465/how-to-capture-stdout-stderr-with-googletest

  protected:
    ObserverTest() : sbuf{nullptr}
    {
      // intentionally empty
    }

    ~ObserverTest() override = default;

    // Called before each unit test
    void SetUp() override
    {
      // Save cout's buffer...
      sbuf = std::cout.rdbuf();
      // Redirect cout to our stringstream buffer or any other ostream
      std::cout.rdbuf(buffer.rdbuf());
    }

    // Called after each unit test
    void TearDown() override
    {
      // When done redirect cout to its old self
      std::cout.rdbuf(sbuf);
      sbuf = nullptr;
    }

    // The following objects can be reused in each unit test

    // This can be an ofstream as well or any other ostream
    std::stringstream buffer{};
    // Save cout's buffer here
    std::streambuf *sbuf;

  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  TEST_F(ObserverTest, ObserverOnEventTest)
  {
    entity_project::EntityConsoleLogger obs;

    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "notify");
    JsonHelper::AddStringToJsonObject(obj, "value", "scheduled");
    picojson::value val = JsonHelper::ConvertPicojsonObjectToValue(obj);

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

    std::string expected
    {"Entity #0: {\"type\":\"notify\",\"value\":\"scheduled\"}\n"};
      obs.OnEvent(val, *package);
      std::string actual{buffer.str()};
      EXPECT_EQ(expected, actual);
    }

} // namespace csci3081

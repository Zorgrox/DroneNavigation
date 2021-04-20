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
  class ObserverTest : public ::testing::Test
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

  // Test the observer pattern through mocking up the delivery system
  TEST_F(ObserverTest, NotificationTest)
  {
  }

} // namespace csci3081

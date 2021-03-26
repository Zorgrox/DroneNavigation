#include "gtest/gtest.h"
#include "vector2d.h"

#include <iostream>

namespace csci3081
{
  class Vector2DTest : public ::testing::Test
  {
  protected:
    std::vector<float> vel{0, 3};
    std::vector<float> pos{2, 5};
  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  // Test Vector2D constructor
  TEST_F(Vector2DTest, Vector2DConstructorTest)
  {
    Vector2D* vec = new Vector2D(pos, vel);
    std::vector<float> expected_vel{0, 3};
    std::vector<float> expected_pos{2, 5};

    ASSERT_EQ(vec->GetVelocity(), expected_vel);
    ASSERT_EQ(vec->GetPosition(), expected_pos);

  }

  TEST_F(Vector2DTest, Vector2DCalculationsTest)
  {
    Vector2D *vec = new Vector2D(pos, vel);
    std::vector<float> expected_vel{0, 3};
    std::vector<float> expected_pos{2, 5};

    std::vector<float> expected_unit_vector{0, 1};
    ASSERT_EQ(vec->GetUnitVector(), expected_unit_vector);

    float expected_magnitude = 3.0;
    ASSERT_EQ(vec->CalculateMagnitude(), expected_magnitude);

  }

  TEST_F(Vector2DTest, Vector2DSettersTest)
  {

    Vector2D *vec = new Vector2D(pos, vel);
    std::vector<float> expected_vel{0, 3};
    std::vector<float> expected_pos{2, 5};

    std::vector<float> new_vel{2, 2};
    std::vector<float> new_pos{3, 3};

    vec->SetVelocity(new_vel);
    vec->SetPosition(new_pos);

    ASSERT_EQ(vec->GetVelocity(), new_vel);
    // ASSERT_FLOAT_EQ(vec->GetVelocity()[0], new_vel[0]);
    // ASSERT_FLOAT_EQ(vec->GetVelocity()[1], new_vel[1]);

    ASSERT_EQ(vec->GetPosition(), new_pos);
    // ASSERT_FLOAT_EQ(vec->GetPosition()[0], new_pos[0]);
    // ASSERT_FLOAT_EQ(vec->GetPosition()[1], new_pos[1]);
  }
} // namespace csci3081

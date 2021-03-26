#include "gtest/gtest.h"
#include "vector3d.h"

#include <iostream>

namespace csci3081
{
  class Vector3DTest : public::testing::Test
  {
  protected:
    std::vector<float> vel{0, 0, 3};
    std::vector<float> pos{2, 4, 5};
  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  // Test Vector3D constructor
  TEST_F(Vector3DTest, Vector3DConstructorTest)
  {
    Vector3D* vec = new Vector3D(pos, vel);
    std::vector<float> expected_vel{0, 0, 3};
    std::vector<float> expected_pos{2, 4, 5};

    ASSERT_EQ(vec->GetVelocity(), expected_vel);
    ASSERT_EQ(vec->GetPosition(), expected_pos);

  }

  TEST_F(Vector3DTest, Vector3DCalculationsTest)
  {
    Vector3D *vec = new Vector3D(pos, vel);
    std::vector<float> expected_vel{0, 0, 3};
    std::vector<float> expected_pos{2, 4, 5};

    std::vector<float> expected_unit_vector{0, 0, 1};
    ASSERT_EQ(vec->GetUnitVector(), expected_unit_vector);

    float expected_magnitude = 3.0;
    ASSERT_EQ(vec->CalculateMagnitude(), expected_magnitude);

  }

  TEST_F(Vector3DTest, Vector3DSettersTest)
  {
    Vector3D *vec = new Vector3D(pos, vel);
    std::vector<float> expected_vel{0, 0, 3};
    std::vector<float> expected_pos{2, 4, 5};

    std::vector<float> new_vel{2, 2, 2};
    std::vector<float> new_pos{3, 3, 3};

    vec->SetVelocity(new_vel);
    vec->SetPosition(new_pos);

    ASSERT_EQ(vec->GetVelocity(), new_vel);
    ASSERT_EQ(vec->GetPosition(), new_pos);
  }

  TEST_F(Vector3DTest, Vector3DOperationsTest)
  {
    Vector3D *vec = new Vector3D(pos, vel);

    std::vector<float> new_vel{0, 0, 1};
    std::vector<float> new_pos{0, 0, 1};
    Vector3D *vec_2 = new Vector3D(new_pos, new_vel);

    std::vector<float> vec_pos = vec->GetPosition();
    std::vector<float> vec_2_pos = vec_2->GetPosition();
    std::vector<float> added_pos = vec->AddTwoVectors(vec_pos, vec_2_pos);
    std::vector<float> expected_added_pos = {2,4,6};
    ASSERT_EQ(added_pos, expected_added_pos);

    std::vector<float> subtracted_pos = vec->SubtractTwoVectors(vec_pos, vec_2_pos);
    std::vector<float> expected_subtracted_pos = {2, 4, 4};
    ASSERT_EQ(subtracted_pos, expected_subtracted_pos);

    std::vector<float> multiplied_pos = vec->MultiplyVectorWithFloat(vec_pos, 2.0);
    std::vector<float> expected_multiplied_pos = {4, 8, 10};
    ASSERT_EQ(multiplied_pos, expected_multiplied_pos);
  }

} // namespace csci3081

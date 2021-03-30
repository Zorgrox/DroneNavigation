#include "gtest/gtest.h"
#include "vector3d.h"

#include <iostream>

namespace csci3081
{
  class Vector3DTest : public::testing::Test
  {
  protected:
    std::vector<float> std_vec{0, 0, 3};
  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  // Test Vector3D constructor
  TEST_F(Vector3DTest, Vector3DConstructorTest)
  {
    Vector3D* vec = new Vector3D(std_vec);
    std::vector<float> expected_vec{0, 0, 3};

    ASSERT_EQ(vec->GetVector(), expected_vec);
  }

  TEST_F(Vector3DTest, Vector3DCalculationsTest)
  {
    Vector3D *vec = new Vector3D(std_vec);

    float expected_magnitude = 3.0;
    ASSERT_EQ(vec->CalculateMagnitude(), expected_magnitude);

    vec->Normalize();
    std::vector<float> expected_unit_vector{0, 0, 1};
    ASSERT_EQ(vec->GetVector(), expected_unit_vector);

  }

  TEST_F(Vector3DTest, Vector3DSettersTest)
  {
    Vector3D *vec = new Vector3D(std_vec);

    std::vector<float> new_vec{2, 2, 2};
    vec->SetVector(new_vec);

    ASSERT_EQ(vec->GetVector(), new_vec);
  }

  TEST_F(Vector3DTest, Vector3DOperationsTest)
  {
    Vector3D *vec = new Vector3D(std_vec);

    std::vector<float> new_vec{0, 0, 1};
    Vector3D *vec_2 = new Vector3D(new_vec);

    std::vector<float> vec_pos = vec->GetVector();
    std::vector<float> vec_2_pos = vec_2->GetVector();
    std::vector<float> added_pos = vec->AddTwoVectors(vec_pos, vec_2_pos);
    std::vector<float> expected_added_pos = {0,0,4};
    ASSERT_EQ(added_pos, expected_added_pos);

    std::vector<float> subtracted_pos = vec->SubtractTwoVectors(vec_pos, vec_2_pos);
    std::vector<float> expected_subtracted_pos = {0, 0, 2};
    ASSERT_EQ(subtracted_pos, expected_subtracted_pos);

    std::vector<float> multiplied_pos = vec->MultiplyVectorWithFloat(vec_pos, 2.0);
    std::vector<float> expected_multiplied_pos = {0, 0, 6};
    ASSERT_EQ(multiplied_pos, expected_multiplied_pos);
  }

} // namespace csci3081

#include "gtest/gtest.h"
#include "vector2d.h"

#include <iostream>

namespace csci3081
{
  class Vector2DTest : public ::testing::Test
  {
  protected:
    std::vector<float> vec_2d{0, 0, 3};
  };

  /*******************************************************************************
 * Test Cases
 ******************************************************************************/

  // Test Vector2D constructor
  TEST_F(Vector2DTest, Vector2DConstructorTest)
  {
    Vector2D* vec = new Vector2D(vec_2d);

    ASSERT_EQ(vec->GetVector(), vec_2d);
  }

  TEST_F(Vector2DTest, Vector2DCalculationsTest)
  {
    Vector2D *vec = new Vector2D(vec_2d);

    float expected_magnitude = 3.0;
    ASSERT_EQ(vec->CalculateMagnitude(), expected_magnitude);

    std::vector<float> expected_unit_vector{0, 0, 1};
    vec->Normalize();
    ASSERT_EQ(vec->GetVector(), expected_unit_vector);

  }

  TEST_F(Vector2DTest, Vector2DSettersTest)
  {
    Vector2D *vec = new Vector2D(vec_2d);
    std::vector<float> new_vector{0, 0, 1};
    vec->SetVector(new_vector);
    ASSERT_EQ(vec->GetVector(), new_vector);
  }

  TEST_F(Vector2DTest, Vector2DOperationsTest)
  {
    Vector2D *vec = new Vector2D(vec_2d);

    std::vector<float> new_vec{0, 0, 1};
    Vector2D *vec_2 = new Vector2D(new_vec);

    std::vector<float> vec_pos = vec->GetVector();
    std::vector<float> vec_2_pos = vec_2->GetVector();
    std::vector<float> added_pos = vec->AddTwoVectors(vec_pos, vec_2_pos);
    std::vector<float> expected_added_pos = {0, 0, 4};
    ASSERT_EQ(added_pos, expected_added_pos);

    std::vector<float> subtracted_pos = vec->SubtractTwoVectors(vec_pos, vec_2_pos);
    std::vector<float> expected_subtracted_pos = {0, 0, 2};
    ASSERT_EQ(subtracted_pos, expected_subtracted_pos);

    std::vector<float> multiplied_pos = vec->MultiplyVectorWithFloat(vec_pos, 2.0);
    std::vector<float> expected_multiplied_pos = {0, 0, 6};
    ASSERT_EQ(multiplied_pos, expected_multiplied_pos);
  }
} // namespace csci3081

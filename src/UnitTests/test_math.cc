
#include "../Math/type.h"
#include "../Math/multithread.h"

#include "gtest/gtest.h"
// ASSERT_EQ, ASSERT_FALSE, ASSERT_GE, ASSERT_GT, ASSERT_LE, ASSERT_LT, ASSERT_NE, ASSERT_TRUE,
// EXPECT_FALSE, EXPECT_TRUE
// FAIL, SUCCEED
// TEST, or TEST_F

TEST(TestMath, test_solvePolynom3)
{
    float p1 = 0, p2 = 0, p3 = 0;
    ASSERT_EQ(U1::Math::solvePolynom3(p1, p2, p3, 1.0f, 2.0f, -3.0f), 1);
    ASSERT_TRUE(U1::Math::equals((p1 * p1 * p1) + (p1 * p1) + p1 * 2.0f - 3.0f, 0.0f));

    ASSERT_EQ(U1::Math::solvePolynom3(p1, p2, p3, -6.0f, 11.0f, -6.0f), 3);
    ASSERT_TRUE(U1::Math::equals(p1, 1.0f));
    ASSERT_TRUE(U1::Math::equals(p2, 3.0f));
    ASSERT_TRUE(U1::Math::equals(p3, 2.0f));
}

TEST(TestMath, test_fillSteps)
{
    std::vector<float> tmp;

    ASSERT_EQ(U1::Math::fillSteps(tmp, 0.0f, 1.0f, 1.0f), size_t(2UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], 0.0f));
    ASSERT_TRUE(U1::Math::equals(tmp[1], 1.0f));

    ASSERT_EQ(U1::Math::fillSteps(tmp, -0.1f, 1.0f, 1.0f), size_t(3UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], -0.1f));
    ASSERT_TRUE(U1::Math::equals(tmp[1], 0.0f));
    ASSERT_TRUE(U1::Math::equals(tmp[2], 1.0f));

    ASSERT_EQ(U1::Math::fillSteps(tmp, -0.2f, -0.1f, 1.0f), size_t(2UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], -0.2f));
    ASSERT_TRUE(U1::Math::equals(tmp[1], -0.1f));

    ASSERT_EQ(U1::Math::fillSteps(tmp, -1.2f, -0.1f, 1.0f), size_t(3UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], -1.2f));
    ASSERT_TRUE(U1::Math::equals(tmp[1], -1.0f));
    ASSERT_TRUE(U1::Math::equals(tmp[2], -0.1f));

    ASSERT_EQ(U1::Math::fillSteps(tmp, -0.1f, 1.1f, 1.0f), size_t(4UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], -0.1f));
    ASSERT_TRUE(U1::Math::equals(tmp[1], 0.0f));
    ASSERT_TRUE(U1::Math::equals(tmp[2], 1.0f));
    ASSERT_TRUE(U1::Math::equals(tmp[3], 1.1f));

    ASSERT_EQ(U1::Math::fillAlignedSteps(tmp, 0.0f, 1.0f, 1.0f), size_t(2UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], 0.0f));
    ASSERT_TRUE(U1::Math::equals(tmp[1], 1.0f));

    ASSERT_EQ(U1::Math::fillAlignedSteps(tmp, -0.1f, 1.0f, 1.0f), size_t(2UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], 0.0f));
    ASSERT_TRUE(U1::Math::equals(tmp[1], 1.0f));

    ASSERT_EQ(U1::Math::fillAlignedSteps(tmp, -0.1f, 1.1f, 1.0f), size_t(2UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], 0.0f));
    ASSERT_TRUE(U1::Math::equals(tmp[1], 1.0f));

    ASSERT_EQ(U1::Math::fillAlignedSteps(tmp, 0.1f, 0.2f, 1.0f), size_t(0UL));

    ASSERT_EQ(U1::Math::fillAlignedSteps(tmp, 0.0f, 0.2f, 1.0f), size_t(1UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], 0.0f));

    ASSERT_EQ(U1::Math::fillAlignedSteps(tmp, 0.1f, 1.0f, 1.0f), size_t(1UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], 1.0f));

    ASSERT_EQ(U1::Math::fillAlignedSteps(tmp, 0.1f, 1.1f, 1.0f), size_t(1UL));
    ASSERT_TRUE(U1::Math::equals(tmp[0], 1.0f));
}

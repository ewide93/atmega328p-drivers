#include "unity.h"
#include "lrc.h"
#include "types.h"

U8 TestArray[5] = { 1, 2, 3, 4, 5 };

void setUp(void)
{

}

void tearDown(void)
{

}

void test_CalculateLRC(void)
{
    TEST_ASSERT_EQUAL(241, LRC_Calc(TestArray, 5));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_CalculateLRC);

    return UNITY_END();
}
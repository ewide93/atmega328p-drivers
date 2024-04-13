#include "unity.h"
#include "fsm.h"
#include "types.h"

FSMType TestFsm;

typedef enum
{
    TEST_STATE_NONE = 0,
    TEST_STATE_INIT = 1,
    TEST_STATE_TWO = 2,
    TEST_STATE_THREE = 3,
    TEST_STATE_FOUR = 4
} TestStatesEnum;

void setUp(void)
{
    FSM_Init(&TestFsm);
}

void tearDown(void)
{

}

void test_InitStateMachine(void)
{
    TEST_ASSERT_EQUAL(TEST_STATE_INIT, FSM_GetCurrentState(&TestFsm));
    TEST_ASSERT_EQUAL(TEST_STATE_NONE, FSM_GetPreviousState(&TestFsm));
}

void test_AdvanceStateOnce(void)
{
    FSM_SetState(&TestFsm, TEST_STATE_TWO);
    TEST_ASSERT_EQUAL(TEST_STATE_TWO, FSM_GetCurrentState(&TestFsm));
    TEST_ASSERT_EQUAL(TEST_STATE_INIT, FSM_GetPreviousState(&TestFsm));
}

void test_AdvanceStateMultipleTimes(void)
{
    FSM_SetState(&TestFsm, TEST_STATE_TWO);
    TEST_ASSERT_EQUAL(TEST_STATE_TWO, FSM_GetCurrentState(&TestFsm));
    TEST_ASSERT_EQUAL(TEST_STATE_INIT, FSM_GetPreviousState(&TestFsm));

    FSM_SetState(&TestFsm, TEST_STATE_THREE);
    TEST_ASSERT_EQUAL(TEST_STATE_THREE, FSM_GetCurrentState(&TestFsm));
    TEST_ASSERT_EQUAL(TEST_STATE_TWO, FSM_GetPreviousState(&TestFsm));

    FSM_SetState(&TestFsm, TEST_STATE_FOUR);
    TEST_ASSERT_EQUAL(TEST_STATE_FOUR, FSM_GetCurrentState(&TestFsm));
    TEST_ASSERT_EQUAL(TEST_STATE_THREE, FSM_GetPreviousState(&TestFsm));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_InitStateMachine);
    RUN_TEST(test_AdvanceStateOnce);
    RUN_TEST(test_AdvanceStateMultipleTimes);

    return UNITY_END();
}
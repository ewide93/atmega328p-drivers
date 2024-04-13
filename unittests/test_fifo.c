#include "unity.h"
#include "fifo.h"
#include "types.h"

FifoType TestFifo;
U8 TestArray[8];

void TestArrayClear(void)
{
    for (U8 i = 0; i < 8; i++)
    {
        TestArray[i] = 0;
    }
}

void setUp(void)
{
    TestArrayClear();
    Fifo_Init(&TestFifo, TestArray, 8);
}

void tearDown(void)
{
    Fifo_Clear(&TestFifo);
}

void test_AddTwoItemsAssertCorrectNofItems(void)
{
    Fifo_WriteByte(&TestFifo, 0xFF);
    Fifo_WriteByte(&TestFifo, 0xFF);
    TEST_ASSERT_EQUAL(2, Fifo_GetNofItems(&TestFifo));
}

void test_AddTwoItemsAssertDataValid(void)
{
    U8 a = 0;
    U8 b = 0;
    Fifo_WriteByte(&TestFifo, 0x11);
    Fifo_WriteByte(&TestFifo, 0x12);
    TEST_ASSERT_EQUAL(2, Fifo_GetNofItems(&TestFifo));

    Fifo_ReadByte(&TestFifo, &a);
    Fifo_ReadByte(&TestFifo, &b);
    TEST_ASSERT_EQUAL(0x11, a);
    TEST_ASSERT_EQUAL(0x12, b);
}

void test_OverrunProtection(void)
{
    U8 ResultArray[8] = { 0 };

    while(!Fifo_Full(&TestFifo))
    {
        Fifo_WriteByte(&TestFifo, 50);
    }
    Fifo_WriteByte(&TestFifo, 100);
    Fifo_WriteByte(&TestFifo, 100);

    TEST_ASSERT_EQUAL(8, Fifo_GetNofItems(&TestFifo));

    U8 i = 0;
    while(!Fifo_Empty(&TestFifo))
    {
        Fifo_ReadByte(&TestFifo, &ResultArray[i]);
        i++;
    }

    for (U8 j = 0; j < 8; j++)
    {
        TEST_ASSERT_EQUAL(50, ResultArray[j]);
    }
}

void test_ClearFifo(void)
{
    while (!Fifo_Full(&TestFifo))
    {
        Fifo_WriteByte(&TestFifo, 0xAA);
    }
    Fifo_Clear(&TestFifo);

    TEST_ASSERT_EQUAL(TRUE, Fifo_Empty(&TestFifo));
    TEST_ASSERT_EQUAL(8, Fifo_GetNofAvailable(&TestFifo));
    for (U8 i = 0; i < 8; i++)
    {
        TEST_ASSERT_EQUAL(0, TestArray[i]);
    }

}

void test_WrapAround(void)
{
    U8 Dummy = 0;
    U8 Results[8] = { 0 };
    U8 Expected[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xEE, 0xEE, 0xEE, 0xEE };

    while (!Fifo_Full(&TestFifo))
    {
        Fifo_WriteByte(&TestFifo, 0xFF);
    }

    TEST_ASSERT_EQUAL(8, Fifo_GetNofItems(&TestFifo));

    for (U8 i = 0; i < 4; i++)
    {
        Fifo_ReadByte(&TestFifo, &Dummy);
    }

    TEST_ASSERT_EQUAL(4, Fifo_GetNofItems(&TestFifo));
    TEST_ASSERT_EQUAL(4, Fifo_GetNofAvailable(&TestFifo));

    for (U8 i = 0; i < 4; i++)
    {
        Fifo_WriteByte(&TestFifo, 0xEE);
    }

    U8 j = 0;
    while (!Fifo_Empty(&TestFifo))
    {
        Fifo_ReadByte(&TestFifo, &Results[j]);
        j++;
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY(Expected, Results, 8);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_AddTwoItemsAssertCorrectNofItems);
    RUN_TEST(test_AddTwoItemsAssertDataValid);
    RUN_TEST(test_OverrunProtection);
    RUN_TEST(test_ClearFifo);
    RUN_TEST(test_WrapAround);

    return UNITY_END();
}
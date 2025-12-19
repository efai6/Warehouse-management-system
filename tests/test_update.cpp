#include <gtest/gtest.h>

extern "C" {
#include "object.h"
#include "update.h"
}

TEST(UpdateTest, PlusOperation) {
    Object obj = {"AAAAA", "Test", 10};

    int res = apply_update_count(&obj, '+', 5);

    EXPECT_EQ(res, 0);
    EXPECT_EQ(obj.quantity, 15);
}

TEST(UpdateTest, MinusOperation) {
    Object obj = {"BBBBB", "Test", 10};

    int res = apply_update_count(&obj, '-', 3);

    EXPECT_EQ(res, 0);
    EXPECT_EQ(obj.quantity, 7);
}

TEST(UpdateTest, MinusTooMuch) {
    Object obj = {"CCCCC", "Test", 5};

    int res = apply_update_count(&obj, '-', 10);

    EXPECT_EQ(res, 2);
    EXPECT_EQ(obj.quantity, 5);
}

TEST(UpdateTest, InvalidOperator) {
    Object obj = {"DDDDD", "Test", 5};

    int res = apply_update_count(&obj, '*', 2);

    EXPECT_EQ(res, 1);
}

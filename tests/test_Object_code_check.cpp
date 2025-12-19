#include <gtest/gtest.h>

extern "C" {
#include "object.h"
#include "Object_code_check.h"
}

TEST(CodeTest, GoodCode) {
    char code[] = "AA034";

    int res = Object_code_check(code);

    EXPECT_EQ(res, 0);
}

TEST(CodeTest, Bad1Ch) {
    char code[] = "*A034";

    int res = Object_code_check(code);

    EXPECT_EQ(res, 1);
}

TEST(CodeTest, Bad2Ch) {
    char code[] = "A/034";

    int res = Object_code_check(code);

    EXPECT_EQ(res, 1);
}

TEST(CodeTest, Bad3Ch) {
    char code[] = "AAS34";

    int res = Object_code_check(code);

    EXPECT_EQ(res, 1);
}
TEST(CodeTest, Bad4Ch) {
    char code[] = "AA0;4";

    int res = Object_code_check(code);

    EXPECT_EQ(res, 1);
}
TEST(CodeTest, Bad5Ch) {
    char code[] = "AA03G";

    int res = Object_code_check(code);

    EXPECT_EQ(res, 1);
}
TEST(CodeTest, TooLongCode) {
    char code[] = "AA034H";

    int res = Object_code_check(code);

    EXPECT_EQ(res, 1);
}

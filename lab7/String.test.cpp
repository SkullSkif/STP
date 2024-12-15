#include "String.hpp"
#include <gtest/gtest.h>

TEST(StringTest, DefaultConstructor) {
    String s;
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_EQ(s.size(), 0);
}

TEST(StringTest, CStringConstructor) {
    String s("hello");
    EXPECT_STREQ(s.c_str(), "hello");
    EXPECT_EQ(s.size(), 5);
}

TEST(StringTest, CopyConstructor) {
    String s1("hello");
    String s2(s1);
    EXPECT_STREQ(s2.c_str(), "hello");
    EXPECT_EQ(s2.size(), 5);
}

TEST(StringTest, CopyAssignment) {
    String s1("hello");
    String s2;
    s2 = s1;
    EXPECT_STREQ(s2.c_str(), "hello");
    EXPECT_EQ(s2.size(), 5);
}

TEST(StringTest, MoveConstructor) {
    String s1("hello");
    String s2(std::move(s1));
    EXPECT_STREQ(s2.c_str(), "hello");
    EXPECT_EQ(s2.size(), 5);
}

TEST(StringTest, MoveAssignment) {
    String s1("hello");
    String s2;
    s2 = std::move(s1);
    EXPECT_STREQ(s2.c_str(), "hello");
    EXPECT_EQ(s2.size(), 5);
}

TEST(StringTest, AtMethod) {
    String s("hello");
    EXPECT_EQ(s.at(0), 'h');
    EXPECT_EQ(s.at(4), 'o');
    EXPECT_THROW(s.at(5), std::out_of_range);
}

TEST(StringTest, NullCString) {
    String s(nullptr);
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_EQ(s.size(), 0);
}
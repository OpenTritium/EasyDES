#include "gtest/gtest.h"
#include "../../src/key_gen.hpp"
TEST(opts,strip_check_bits){
    Key k{0x7F};
    Key j{0xFF};
    EXPECT_EQ(k.splitAndStripCheckBits().first.full, j.splitAndStripCheckBits().first.full);
    Key m{0xFFFFFFFFFFFFFFFF};
    auto t{m.splitAndStripCheckBits()};
    EXPECT_EQ(t.first.valid,t.second.valid);
    EXPECT_EQ(t.first.valid,0b1111111111111111111111111111);
    Key d{0x80000000};
    EXPECT_EQ(d.splitAndStripCheckBits().first.valid, 0);
}
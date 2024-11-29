#include "gtest/gtest.h"
#include "../../src/key_gen.hpp"

TEST(opts, left_shift){
    HalfKey h{.valid= 0b1000000000000000000000000000};
    HalfKey l{.valid= 0b1000000000000000000000000000};
    h.leftShift(1);
    l.leftShift(2);
    EXPECT_EQ(h.valid,1 );
    h.leftShift(1);
    EXPECT_EQ(h.valid, l.valid);
}
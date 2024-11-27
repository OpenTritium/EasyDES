#include "gtest/gtest.h"
#include "../../src/block.hpp"
TEST(opts,swap_low_high_check){
    const Block b{.data{.low=0,.high=0xFFFFFFFF}};
    EXPECT_EQ(b.swapLowHigh().getFull(), 0xFFFFFFFF);
}
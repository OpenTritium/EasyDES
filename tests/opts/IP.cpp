#include "gtest/gtest.h"
#include "../../src/block.cpp"
int main(){
    Block b {.data = 0b1000000000000000000000000000000000000000};
    EXPECT_EQ(b.initiallyPermutate().data, 1);
}
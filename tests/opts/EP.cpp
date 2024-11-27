#include "../../src/utils.hpp"
#include "gtest/gtest.h"
#include <cstdint>
#include <print>

TEST(opts, EP_check) {
  //{0, 3, 4, 7, 8, 11, 12, 15, 16, 19,20, 23, 24, 27, 28, 31}};
  const auto result{permute<uint64_t,uint32_t,48>(EP,0b10011001100110010001100110011001UL)};
  EXPECT_EQ(result, 0b110011110011110011110010100011110011110011110011ULL);
}
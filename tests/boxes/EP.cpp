#include "../../src/utils.hpp"
#include "gtest/gtest.h"
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

TEST(boxes, EP_check) {
  EXPECT_EQ(std::unordered_set<uint8_t>(EP.cbegin(), EP.cend()).size(), 32);
  auto toBeFound{std::unordered_set<uint8_t>{0, 3, 4, 7, 8, 11, 12, 15, 16, 19,
                                             20, 23, 24, 27, 28, 31}};
  std::unordered_map<uint8_t, uint8_t> counter{};
  for (const auto &e : EP) {
    counter[e]++;
  }
  auto wasFound{std::unordered_set<uint8_t>{}};
  for (const auto &[k, v] : counter) {
    if (v == 2)
      wasFound.insert(k);
  }
  EXPECT_EQ(toBeFound, wasFound);
}
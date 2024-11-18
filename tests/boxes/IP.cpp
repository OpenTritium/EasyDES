#pragma once
#include "../../src/Block.cpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <gtest/gtest.h>
#include <print>
#include <unordered_set>

int main() {
  EXPECT_EQ(IP.size(), 64);
  auto set{std::unordered_set<uint8_t>(IP.cbegin(), IP.cend())};
  EXPECT_EQ(*std::min_element(set.cbegin(), set.cend()), 0);
  EXPECT_EQ(*std::max_element(set.cbegin(), set.cend()), 63);
}
#pragma once
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <print>
#include <ranges>

static constexpr std::array<uint8_t, 64> IP{
    57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7,
    56, 48, 40, 32, 24, 16, 8,  0, 58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6};

static constexpr std::array<uint8_t, 48> EP{
    31, 0,  1,  2,  3,  4,  3,  4,  5,  6,  7,  8,  7,  8,  9,  10,
    11, 12, 11, 12, 13, 14, 15, 16, 15, 16, 17, 18, 19, 20, 19, 20,
    21, 22, 23, 24, 23, 24, 25, 26, 27, 28, 27, 28, 29, 30, 31, 0};

template <typename O, typename I, size_t N>
[[nodiscard]]
static constexpr O permute(const std::array<uint8_t, N> &box,
                           const I bufferRead) {
  O buffer{};
  for (const auto &[index, offset] : box | std::views::enumerate) {
    if ((bufferRead >> offset & 1) != 0) {
      O mask{std::integral_constant<O, 1>::value << index};
      buffer |= mask;
    }
  }
  return buffer;
}
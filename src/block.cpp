#pragma once
#include <cstdint>
#include <print>
#include <ranges>
#include "static_assets.cpp"


struct Block {
  uint64_t data{};
  Block initiallyPermutate() {
    Block result{}; // all bits are zero by default
    for (const auto &[index, offset] : IP | std::views::enumerate) {
      if ((data >> index & 1) != 0) {
        uint64_t mask{1ull << offset};
        result.data |= mask;
      }
    }
    return result;
  }
  uint32_t getLowPart() noexcept {
    return *reinterpret_cast<uint32_t *>(&data);
  }
  uint32_t getHighPart() noexcept {
    return *(reinterpret_cast<uint32_t *>(&data) + 1);
  }
};
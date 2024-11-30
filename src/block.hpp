#pragma once
#include <cstdint>

struct Block {
  union {
    uint64_t full{};
    struct {
      uint32_t low;
      uint32_t high;
    };
  } data;
  uint32_t getLowPart() const noexcept { return data.low; }
  uint32_t getHighPart() const noexcept { return data.high; }
  uint64_t getFull() const noexcept { return data.full; }
  Block swapLowHigh() const noexcept {
    return {.data{.low = getHighPart(), .high = getLowPart()}};
  }
};
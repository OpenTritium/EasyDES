#pragma once
#include <array>
#include <cstdint>

constexpr uint8_t VALID_BITS_HALF_COUNT{28};
static constexpr std::array<uint8_t, 16> shiftTable{1, 1, 2, 2, 2, 2, 2, 2,
                                                    1, 2, 2, 2, 2, 2, 2, 1};
union HalfKey {
  uint32_t full;
  struct {
    uint32_t valid : VALID_BITS_HALF_COUNT;
    uint32_t padding : 32 - VALID_BITS_HALF_COUNT;
  };
  void leftShift(uint8_t bitCount) noexcept {
    const uint32_t mask{bitCount == 2 ? 0b110000000000000000000000000000U
                                      : 0b010000000000000000000000000000U};
    full <<= bitCount;
    full |= ((full & mask) >> VALID_BITS_HALF_COUNT);
  }
};
struct Key {

  union {
    uint64_t full{};
    struct {
      HalfKey low;
      HalfKey high;
    };
    struct {
      uint8_t p0;
      uint8_t p1;
      uint8_t p2;
      uint8_t p3;
      uint8_t p4;
      uint8_t p5;
      uint8_t p6;
      uint8_t p7;
    };
  } data;
  [[nodiscard]]
  bool checkEvenParity() const noexcept {
    const auto ps{std::array<uint8_t, 8>{data.p0, data.p1, data.p2, data.p3,
                                         data.p4, data.p5, data.p6, data.p7}};
    uint8_t parity{};
    for (const auto e : ps) {
      for (std::size_t i{}; i != 8; ++i) {
        parity ^= (e >> i) & 1;
      }
    }
    return parity == 0 ? true : false;
  }
  auto splitAndStripCheckBits() const noexcept {
    auto stripCheckBits{[](std::array<uint8_t, 4> &&t) {
      constexpr uint8_t validBitsMask{0b01111111};
      HalfKey half{};
      std::size_t i{};
      while (true) {
        half.full |= (t[i] & validBitsMask);
        if (++i == 4)
          break;
        half.full <<= 7;
      }
      return half;
    }};
    // caution: little-end
    return std::make_pair(
        stripCheckBits(std::array{data.p3, data.p2, data.p1, data.p0}),
        stripCheckBits(std::array{data.p7, data.p6, data.p5, data.p4}));
  }
  uint64_t mergeLowHigh() const noexcept {
    uint64_t result{};
    result |= data.high.valid;
    result <<= VALID_BITS_HALF_COUNT;
    result |= data.low.valid;
    return result;
  }
};
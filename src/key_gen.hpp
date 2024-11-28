#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>

struct Key {
  using HalfKey = union {
    uint32_t full;
    struct {
      uint32_t valid : 28;
      uint32_t padding : 4;
    };
  };
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
  static constexpr std::array<uint8_t, 16> shiftTable{1, 1, 2, 2, 2, 2, 2, 2,
                                                      1, 2, 2, 2, 2, 2, 2, 1};
  [[nodiscard]]
  bool checkEvenParity() const noexcept {
    const auto ps{std::array<uint8_t, 8>{data.p0, data.p1, data.p2, data.p3,
                                         data.p4, data.p5, data.p6, data.p7}};
    uint8_t parity{};
    for (const auto e : ps) {
      for (size_t i{}; i != 8; ++i) {
        parity ^= (e >> i) & 1;
      }
    }
    return parity == 0 ? true : false;
  }
  auto splitAndStripCheckBits() {
    uint32_t low{}, high{};
    constexpr uint8_t validBitsMask{0b01111111};

    auto stripCheckBits{[](std::array<uint8_t, 4> &&t) {
      uint32_t half{};
      size_t i{};
      while (i != 4) {
        half |= (t[i] & validBitsMask);
        ++i;
        if (i == 4)
          break;
        half <<= 7;
      }
      return half;
    }};
    return std::make_pair(
        stripCheckBits(std::array{data.p0, data.p1, data.p2, data.p3}),
        stripCheckBits(std::array{data.p4, data.p5, data.p6, data.p7}));
  }
};

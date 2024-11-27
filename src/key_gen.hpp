#include <array>
#include <cstdint>
struct Key {
  union {
    uint64_t full{};
    struct {
      uint32_t low;
      uint32_t high;
    };
    struct {
      uint8_t p0;
      uint8_t p1;
      uint8_t p2;
      uint8_t p3;
    };
  } data;
  bool evenParity() {
    const auto ps{std::array<uint8_t, 4>{data.p0, data.p1, data.p2, data.p3}};
    uint8_t parity{};
    for (const auto e : ps) {
      for (size_t i{}; i != 8; ++i) {
        parity ^= (e >> i) & 1;
      }
    }
    return parity == 0 ? true : false;
  }
};
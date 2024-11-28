#include "key_gen.hpp"
#include "utils.hpp"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <print>

using SubKey = union {
  uint32_t full;
  struct {
    uint32_t valid : 28;
    uint32_t padding : 4;
  };
};

int main() {
  Key k{0xFFFFFFFFFFFFFFFF};
  std::cout << k.checkEvenParity() << std::endl;
  std::cout << std::bitset<32>(k.splitAndStripCheckBits().second) << std::endl;
}
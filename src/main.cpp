#pragma once
#include "block.cpp"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <print>
#include "./static_assets.cpp"
// plz ensure 8-byte alignment

int main() {
  Block b{0b1000000000000000000000000000000000000000};
  std::cout << std::bitset<64>(b.initiallyPermutate().data) << std::endl;
}

Block round(uint32_t left, uint32_t right) {
  Block result;
  result.data &= right;
  auto rst = mapTo<uint64_t>(EP,right);
  
}
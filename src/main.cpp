#pragma once
#include <bitset>
#include <iostream>
#include <print>
#include "Block.cpp"
// plz ensure 8-byte alignment


int main() {
  Block b{0b1000000000000000000000000000000000000000};
  std::cout << std::bitset<64>(b.initiallyPermutate().data) << std::endl;
}

// Block round(uint32_t left,uint32_t right){
// Block result;
// result.data &= right;

// }
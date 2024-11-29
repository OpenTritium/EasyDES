#include "block.hpp"
#include "key_gen.hpp"
#include "utils.hpp"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <print>


int main() {
Block b{0xFFFFFFFFFFFFFFFF};
auto a = permute<uint64_t>(IP, b.getFull());
std::cout << std::bitset<64>(a) << std::endl;
Block bb{a};
std::cout << std::bitset<32>(bb.getHighPart()) << std::endl;
auto extend = permute<uint64_t>(EP, bb.getHighPart());
std::cout << std::bitset<64>(extend) << std::endl;
Key k{0xFFFFFFFFFFFFFFFF};
std::cout << std::bitset<64>(k.mergeLowHigh()) << std::endl;
auto s = permute<uint64_t>(CP, k.mergeLowHigh());
std::cout << std::bitset<64>(s) << std::endl;
}
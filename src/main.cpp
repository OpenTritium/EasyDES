#include "block.hpp"
#include "key_gen.hpp"
#include "utils.hpp"
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <print>

constexpr std::size_t ROUND_COUNT{16};
int main() {
  Block raw{0xFFFFFFFFFFFFFFFF};
  Key k{0xFFFFFFFFFFFFFFFF};
  Block iped{permute<uint64_t>(IP, raw.getFull())}; // 初始置换
  auto nd{iped}; // 用于迭代
  for (std::size_t i{}; i != ROUND_COUNT; ++i) {
    auto [nl, nh] =
        k.splitAndStripCheckBits(); // 解构去除校验位的28位左半部分和右半部分
    nl.leftShift(2);                // 低位部分循环左移
    nh.leftShift(1);                // 高位部分循环左移

    Key nk{.data{.low = nl, .high = nh}}; // 生成本次循环所使用的密钥
    uint64_t cped{permute<uint64_t>(
        CP, nk.mergeLowHigh())}; // 将两个低28位并到低56位，再压缩置换到48位
    auto eped{
        permute<uint64_t>(EP, iped.getHighPart())}; // 将高32位扩展置换到48位
    auto xor1{eped ^ cped}; // 第一次数据高位拓展置换后的结果异或子密钥
    auto sed = substitute(xor1);         // S代替
    auto ped{permute<uint32_t>(P, sed)}; // P置换
    if (i != ROUND_COUNT - 1)            // 最一轮不交换
      nd = nd.swapLowHigh();
    nd.data.high ^= ped; // 第二次异或，与之前的低位（现在的高位）异或
  }
  auto result{permute<uint64_t>(FP, nd.getFull())}; // 末置换
  std::cout << std::bitset<64>(result) << std::endl;
}
#include <array>
#include <cstdint>
#include <iostream>
#include <print>
#include <ranges>
#include <bitset>

// plz ensure 8-byte alignment
struct Block {
  uint64_t data{};
  Block initiallyPermutate() {
    constexpr std::array<uint8_t, 64> IP{
        57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7,
        56, 48, 40, 32, 24, 16, 8,  0, 58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6,
    };
    Block result{}; // all bits are zero by default
    for(const auto&[index,offset]: IP | std::views::enumerate){
        if((data>>index&1)!=0) {
            uint64_t mask{1ull<<offset};
            result.data |= mask;
        }
    }
    return result;
  }
  uint32_t getLowPart() noexcept { return *reinterpret_cast<uint32_t *>(&data); }
  uint32_t getHighPart() noexcept { return *(reinterpret_cast<uint32_t *>(&data) + 1); }
};

int main() {
  Block b{0b1000000000000000000000000000000000000000};
  std::cout << std::bitset<64>(b.initiallyPermutate().data) << std::endl;
}

Block round(uint32_t left,uint32_t right){
Block result;
result.data &= right;

}
#include "utils.hpp"
#include "key_gen.hpp"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <print>
int main(){
    Key k{.data.p0=0x0};
    std::cout << k.evenParity() << std::endl;
}
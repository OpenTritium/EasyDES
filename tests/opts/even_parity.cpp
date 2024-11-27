#include "../../src/key_gen.hpp"
#include "gtest/gtest.h"

TEST(opts, even_parity) {
  const Key all{.data{.full = 0xFFFFFFFFFFFFFFFF}};
  Key magic{.data{.p0 = 1, .p1 = 1, .p2 = 1, .p3 = 1}};
  EXPECT_TRUE(all.checkEvenParity());
  EXPECT_TRUE(magic.checkEvenParity());
  magic.data.full += 2;
  EXPECT_FALSE(magic.checkEvenParity());
}
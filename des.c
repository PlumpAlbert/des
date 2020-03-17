#include "des.h"

unsigned char swap_bits(unsigned char x, char i, char j) {
  char left = (sizeof(unsigned char) * 8 - i);
  char right = (sizeof(unsigned char) * 8 - j);
  unsigned char a = (x >> left) & ((1U << 1) - 1);
  unsigned char b = (x >> right) & ((1U << 1) - 1);
  unsigned char xor = a ^ b;
  xor = (xor << left) | (xor << right);
  printf("xor = %02X\n", xor);
  return x ^ xor;
}

uint64_t ip(uint64_t block) {
return 0;
}
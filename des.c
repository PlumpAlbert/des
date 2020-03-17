#include "des.h"

const unsigned char IP_TABLE[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

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

long ip(long block) {
  long result = 0;
  for (int i = 0; i < sizeof(IP_TABLE); ++i) {
    if (TestBit(block, 64, IP_TABLE[i])) {
      SetBit(result, 64, i);
      // printf("->\tIP[%d]: BLOCK[%d] -> %016lx\n", i, IP_TABLE[i], result);
    } else
      ClearBit(result, 64, i);
  }
  return result;
}

long cycle(long prev) {
  printf("Prev = %016lx\n", prev);
  long L = prev >> 32;
  printf("L\t = %08lx\n", L);
  int R = prev;
  printf("R\t =         %08x\n", R);
  // R = R ^ feistel(prev[1], key);
  return (L << 32) | R;
}
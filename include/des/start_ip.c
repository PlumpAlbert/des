#include "des.h"

const unsigned char START_IP_TABLE[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

unsigned long start_ip(unsigned long block) {
  unsigned long result = 0;
  for (int i = 1; i <= sizeof(START_IP_TABLE); ++i) {
    if (TestBit(block, 64, START_IP_TABLE[i - 1])) {
      SetBit(result, 64, i);
      // printf("->\tIP[%d]: BLOCK[%d] -> %016lx\n", i, START_IP_TABLE[i - 1],
      // result);
    } else
      ClearBit(result, 64, i);
  }
  return result;
}
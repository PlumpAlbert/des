#include "des.h"

const unsigned char END_IP_TABLE[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9,  49, 17, 57, 25};

unsigned long end_ip(unsigned long block) {
  unsigned long result = 0;
  for (int i = 1; i <= sizeof(END_IP_TABLE); ++i) {
    if (TestBit(block, 64, END_IP_TABLE[i - 1])) {
      SetBit(result, 64, i);
      // printf("->\tIP[%d]: BLOCK[%d] -> %016lx\n", i, END_IP_TABLE[i - 1],
      // result);
    } else
      ClearBit(result, 64, i);
  }
  return result;
}
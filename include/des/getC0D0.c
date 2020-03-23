#include "des.h"

const unsigned char C0D0_TABLE[56] = {
    57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34, 26, 18, 10, 2,  59, 51, 43,
    35, 27, 19, 11, 3,  60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7,  62, 54,
    46, 38, 30, 22, 14, 6,  61, 53, 45, 37, 29, 21, 13, 5,  28, 20, 12, 4};

unsigned long extend_key(unsigned char* key) {
  unsigned long extended_key = 0;
  char long_size = sizeof(unsigned long) * 8;
  char char_size = sizeof(unsigned char) * 8;
  for (char i = 1, j = 0, counter = 0; i <= long_size; ++i) {
    if (i % char_size == 0) {
      if (counter % 2 == 1)
        ClearBit(extended_key, long_size, i);
      else
        SetBit(extended_key, long_size, i);
      counter = 0;
      continue;
    }
    if (TestBit(key[j / char_size], char_size, (j % char_size + 1))) {
      // printf("%s-> Key[%d][%d] = %08x%s\n", MAGENTA, j / char_size,
      //        j % char_size, key[j / char_size], RESET);
      SetBit(extended_key, long_size, i);
      counter++;
    } else
      ClearBit(extended_key, long_size, i);
    ++j;
  }
  // printf("%sExtended key: %016lx%s\n", GREEN, extended_key, RESET);
  return extended_key;
}

unsigned char* getC0D0(unsigned long extended_key) {
  unsigned char* newkey = malloc(sizeof(unsigned char) * DES_KEY_LENGTH);
  char long_size = sizeof(unsigned long) * 8;
  char char_size = sizeof(unsigned char) * 8;
  for (char i = 1; i <= sizeof(C0D0_TABLE); ++i) {
    if (TestBit(extended_key, long_size, C0D0_TABLE[i - 1])) {
      SetBit(newkey[i / char_size], char_size, i % char_size);
    } else
      ClearBit(newkey[i / char_size], char_size, i % char_size);
  }
  return newkey;
}
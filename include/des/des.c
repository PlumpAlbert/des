#include "des.h"

#include "colors.h"

const unsigned char START_IP_TABLE[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

const unsigned char END_IP_TABLE[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9,  49, 17, 57, 25};

const unsigned char C0D0_TABLE[56] = {
    57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34, 26, 18, 10, 2,  59, 51, 43,
    35, 27, 19, 11, 3,  60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7,  62, 54,
    46, 38, 30, 22, 14, 6,  61, 53, 45, 37, 29, 21, 13, 5,  28, 20, 12, 4};

const unsigned char SHIFTS[16] = {1, 1, 2, 2, 2, 2, 2, 2,
                                  1, 2, 2, 2, 2, 2, 2, 1};

const unsigned char KI_TABLE[48] = {
    14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10, 23, 19, 12, 4,
    26, 8,  16, 7,  27, 20, 13, 2,  41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

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

unsigned long cycle(unsigned long prev) {
  // printf("Prev = %016lx\n", prev);
  long L = prev >> 32;
  // printf("L\t = %08lx\n", L);
  int R = prev;
  // printf("R\t =         %08x\n", R);
  // R = R ^ feistel(prev[1], key);
  return (L << 32) | R;
}

unsigned char* extend_key(unsigned char* key) {
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
  unsigned char* newkey = malloc(sizeof(unsigned char) * DES_KEY_LENGTH);
  for (char i = 1; i <= sizeof(C0D0_TABLE); ++i) {
    if (TestBit(extended_key, long_size, C0D0_TABLE[i - 1])) {
      SetBit(newkey[i / char_size], char_size, (i % char_size));
    } else
      ClearBit(newkey[i / char_size], char_size, (i % char_size));
  }
  return newkey;
}

unsigned long encrypt(unsigned long data, unsigned char* key) {
  data = start_ip(data);
  unsigned char* ek = extend_key(key);
  unsigned char* ki = NULL;
  for (char i = 1; i <= 16; ++i) {
    // printf("%s-> Cycle #%d%s\n", GREEN, i + 1, RESET);
    ki = generate_ki(ek, i);
    data = cycle(data);
    // printf("\n");
  }
  return end_ip(data);
}

unsigned char* generate_ki(unsigned char* key, char iter) {
  return NULL;
}
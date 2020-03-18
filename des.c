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
  long result = 0;
  for (int i = 0; i < sizeof(START_IP_TABLE); ++i) {
    if (TestBit(block, 64, START_IP_TABLE[i])) {
      SetBit(result, 64, i);
      // printf("->\tIP[%d]: BLOCK[%d] -> %016lx\n", i, START_IP_TABLE[i],
      // result);
    } else
      ClearBit(result, 64, i);
  }
  return result;
}

unsigned long end_ip(unsigned long block) {
  long result = 0;
  for (int i = 0; i < sizeof(END_IP_TABLE); ++i) {
    if (TestBit(block, 64, END_IP_TABLE[i])) {
      SetBit(result, 64, i);
      // printf("->\tIP[%d]: BLOCK[%d] -> %016lx\n", i, END_IP_TABLE[i], result);
    } else
      ClearBit(result, 64, i);
  }
  return result;
}

unsigned long cycle(unsigned long prev) {
  printf("Prev = %016lx\n", prev);
  long L = prev >> 32;
  printf("L\t = %08lx\n", L);
  int R = prev;
  printf("R\t =         %08x\n", R);
  // R = R ^ feistel(prev[1], key);
  return (L << 32) | R;
}

unsigned char const* generate_key() {
  FILE* pFile;
  unsigned char* key = malloc(sizeof(unsigned char) * DES_KEY_LENGTH);

  pFile = fopen("/dev/random", "r");
  if (pFile == NULL) {
    printf("Couldn't open /dev/random.\n\t => Check your privileges\n");
    exit(2);
  }
  fgets(key, DES_KEY_LENGTH, pFile);
  fclose(pFile);
  return key;
}

unsigned long encrypt(unsigned long data) {
  data = start_ip(data);
  unsigned char const* key = generate_key();
  
  for (char i = 0; i < 16; ++i) {
    printf("%s-> Cycle #%d%s\n", GREEN, i + 1, RESET);
    data = cycle(data);
    printf("\n"); 
  }
  return end_ip(data);
}
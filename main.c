#include <stdio.h>
#include "des.h"

int main(int argc, char const *argv[]) {
  unsigned long a = 1ul << 6;
  unsigned char key[7] = {0,0,0,0,0,0,1};
  // printf("Input:\t%016lx\n", a);
  // printf("Key:\t");
  // for (int i = 0; i < 7; ++i)
  //   printf("%08x ", key[i]);
  // printf("\n");
  // printf("Encoded:\t%016lx\n", encrypt(a, key));
  printf("%08x\t->\t%08x\n", 7, (7 << 1) | (7 >> (32 - 1)));
  return 0;
}
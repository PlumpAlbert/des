#include <stdio.h>
#include "./des.h"

int main(int argc, char const *argv[]) {
  unsigned char a = 1;
  printf("a = %02X = %d\n", a, a);
  for (int i = 1; i < 8; i++) {
    unsigned char s = swap_bits(a, 8, 8 - i);
    printf("swap = %02X = %d\n", s, s);
  }
  return 0;
}
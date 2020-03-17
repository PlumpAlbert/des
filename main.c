#include <stdio.h>
#include "des.h"

int main(int argc, char const *argv[]) {
  // unsigned char a = 1;
  // printf("a = %02X = %d\n", a, a);
  // for (int i = 1; i < 8; i++) {
  //   unsigned char s = swap_bits(a, 8, 8 - i);
  //   printf("swap = %02X = %d\n", s, s);
  // }

  long a = 1;
  printf("a: %08lx\n", a);
  long ip_res = ip(a);
  printf("ip: %lu = %016lx\n", ip_res, ip_res);
  printf("%d\n", cycle(1ul << 32));
  return 0;
}
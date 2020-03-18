#include <stdio.h>
#include "des.h"

int main(int argc, char const *argv[]) {
  unsigned long a = 1ul;
  printf("Input:\t%016Lx\n", a);
  printf("Encoded:\t%016Lx\n", encrypt(a));
  return 0;
}
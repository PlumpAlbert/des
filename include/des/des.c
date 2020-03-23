#include "des.h"
#include "colors.h"

unsigned long cycle(unsigned long prev) {
  // printf("Prev = %016lx\n", prev);
  long L = prev >> 32;
  // printf("L\t = %08lx\n", L);
  int R = prev;
  // printf("R\t =         %08x\n", R);
  // R = R ^ feistel(prev[1], key);
  return (L << 32) | R;
}

unsigned long encrypt(unsigned long data, unsigned char* key) {
}
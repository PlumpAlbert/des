#include <unitypes.h>
#include <stdio.h>

#ifndef IP_TABLE
#define IP_TABLE                                                              \
  unsigned char[] {                                                           \
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, \
        38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, \
        17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13,  \
        5, 63, 55, 47, 39, 31, 23, 15, 7                                      \
  }
#endif

/**
 * Sets k-th bit in A
 * @param n - size of A in bits
 */
#define SetBit(A, n, k) (A[(k / n)] |= (1 << (k % n)))
#define ClearBit(A, n, k) (A[(k / n)] &= ~(1 << (k % n)))
#define TestBit(A, n, k) (A[(k / n)] & (1 << (k % n)))

unsigned char swap_bits(unsigned char x, char i, char j);

uint64_t ip(uint64_t);

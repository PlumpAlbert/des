#include <stdio.h>

/**
 * Sets k-th bit in A
 * @param n - size of A in bits
 */
#define SetBit(A, n, k) A |= (1ul << (n - k))
#define ClearBit(A, n, k) A &= ~(1ul << (n - k))
#define TestBit(A, n, k) (A & (1ul << (n - k)))

unsigned char swap_bits(unsigned char x, char i, char j);

long ip(long);
long cycle(long);
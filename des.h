#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/**
 * Sets k-th bit in A
 * @param n - size of A in bits
 */
#define SetBit(A, n, k) A |= (1ul << (n - k))
#define ClearBit(A, n, k) A &= ~(1ul << (n - k))
#define TestBit(A, n, k) (A & (1ul << (n - k)))

#define DES_KEY_LENGTH 7

unsigned char swap_bits(unsigned char x, char i, char j);

unsigned long start_ip(unsigned long);
unsigned long end_ip(unsigned long);
unsigned long cycle(unsigned long);
unsigned char const* generate_key();
unsigned long encrypt(unsigned long);
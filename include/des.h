#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/**
 * Sets k-th bit in A
 * @param n - size of A in bits
 */
#define SetBit(A, n, k) A |= (1ul << (n - (k)))
#define ClearBit(A, n, k) A &= ~(1ul << (n - (k)))
#define TestBit(A, n, k) (A & (1ul << (n - (k))))

#define DES_KEY_LENGTH 7

unsigned long start_ip(unsigned long);
unsigned long end_ip(unsigned long);
unsigned long extend_key(unsigned char *key);
unsigned char* getC0D0(unsigned long);
unsigned char* generate_ki(unsigned char*, char);
unsigned long cycle(unsigned long);
unsigned long encrypt(unsigned long, unsigned char *);
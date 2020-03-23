#include <stdio.h>
#include "des.h"

void print_arg(char*, char*);
void usage();

int main(int argc, char const *argv[]) {
  unsigned long a = 1ul << 6;
  unsigned char key[7] = {0,0,0,0,0,0,1};
  // printf("Input:\t%016lx\n", a);
  // printf("Key:\t");
  // for (int i = 0; i < 7; ++i)
  //   printf("%08x ", key[i]);
  // printf("\n");
  // printf("Encoded:\t%016lx\n", encrypt(a, key));
  // printf("%08x\t->\t%08x\n", 7, (7 << 1) | (7 >> (32 - 1)));
  usage();
  return 0;
}

void usage() {
  printf("USAGE:\n");
  printf("\tdes [-o OUT_FILE] [-k KEY] [--save-key] FILE\n");
  printf("OPTIONS:\n");
  print_arg("-o <OUT_FILE>", "Path to save encoded file");
  print_arg("-k <KEY>", "Key to use for encryption. Either filename or a string");
  print_arg("FILE", "File to encrypt");
  printf("FLAGS:\n");
  print_arg("--save-key", "Save the extended key into the file");
  exit(1);
}

void print_arg(char* arg, char* description) {
  printf("\t%-15s\t\t%s\n", arg, description);
}
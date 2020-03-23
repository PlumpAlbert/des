#include "colors.h"
#include "des.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

void print_arg(char *, char *);
void usage();

typedef struct {
  char const *src;
  char const *dest;
  FILE *key_file;
  char const *key;
  char key_is_file;
  char save_key;
} OPTIONS;

int main(int argc, char const *argv[]) {
  if (argc < 2)
    usage();
  OPTIONS o;
  memset(&o, 0, sizeof(OPTIONS));

  for (char i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'o')
        o.dest = argv[++i];
      if (argv[i][1] == 'k') {
        if (access(argv[++i], R_OK) != 0) {
          o.key_is_file = 0;
          o.key = argv[i];
        } else {
          o.key_is_file = 1;
          o.key_file = fopen(argv[i], "rb");
        }
      }
      if (strcmp(argv[i], "--save-key") == 0)
        o.save_key = 1;
      if (argv[i][1] == 'h' || strcmp(argv[i], "--help") == 0) {
        usage();
        exit(0);
      }
    } else {
      if (access(argv[i], R_OK) != 0) {
        printf(
            "%s! ERROR !\nCan't access file `%s`. Check your permissions.%s\n",
            RED, argv[i], RESET);
        exit(1);
      } else
        o.src = argv[i];
    }
  }

  if (o.dest == NULL) {
    o.dest = malloc(sizeof(char) * 1024);
    printf("Source: %s\n", o.src);
    strcpy(o.dest, o.src);
    strcat(o.dest, ".des");
    printf("Destination: %s\n", o.dest);
  }

  unsigned long data;
  unsigned long ek;
  if (o.key_is_file == 0)
    ek = extend_key(o.key);
  else
    fscanf(o.key_file, "%lu", &ek);
  if (o.save_key == 1) {
    char buf[1024];
    strcat(buf, o.src);
    strcat(buf, ".key");
    o.key_file = fopen(buf, "w+b");
    fprintf(o.key_file, "%lu", ek);
  }
  unsigned char *c0d0 = getC0D0(ek);
  unsigned long counter = 0;
  FILE *src = fopen(o.src, "rb"), *dest = fopen(o.dest, "wb");
  while (fread(&data, sizeof(unsigned long), 1, src) != 0) {
    data = start_ip(data);
    unsigned char *ki = NULL;
    for (char i = 1; i <= 16; ++i) {
      // printf("%s-> Cycle #%d%s\n", GREEN, i + 1, RESET);
      ki = generate_ki(c0d0, i);
      data = cycle(data);
      // printf("\n");
    }
    fprintf(dest, "%lu", end_ip(data));
    counter++;
    printf("%sBytes encoded %d\r", CYAN, counter * 8, RESET);
  }
  printf("\ncounter: %d\n", counter);
  return 0;
}

void usage() {
  printf("USAGE:\n");
  printf("\tdes [-o OUT_FILE] [-k KEY] [--save-key] FILE\n");
  printf("OPTIONS:\n");
  print_arg("-o <OUT_FILE>", "Path to save encoded file");
  print_arg("-k <KEY>",
            "Key to use for encryption. Either filename or a string");
  print_arg("FILE", "File to encrypt");
  printf("FLAGS:\n");
  print_arg("--save-key", "Save the extended key into the file");
  exit(1);
}

void print_arg(char *arg, char *description) {
  printf("\t%-15s\t\t%s\n", arg, description);
}
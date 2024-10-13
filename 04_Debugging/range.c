
#include <stdio.h>
#include <stdlib.h>

void range(int start, int stop, int step) {
  for (int i = start; i < stop; i += step) {
    printf("%i\n", i);
  }
}

void print_help() {
  printf("Usage:\n"
         "\t./range N\tshow: 0, 1, 2, ... N-1\n"
         "\t./range M N\tshow: M, M+1, M+2, ... N-1\n"
         "\t./range N M S\tshow: M, M+S, M+2S, ... N-S\n");
}

int main(int argc, char *argv[]) {
  switch (argc) {
  case 2:
    range(0, atoi(argv[1]), 1);
    break;
  case 3:
    range(atoi(argv[1]), atoi(argv[2]), 1);
    break;
  case 4:
    range(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    break;
  default:
    print_help();
    break;
  }
  return 0;
}

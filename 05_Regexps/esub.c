
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXGR 10

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Need only three parameters!\n");
    return 0;
  }

  regex_t regex;
  regmatch_t bags[MAXGR];
  size_t error_buffer_size = 1000;
  char error_buffer[1000];
  int status = 0;
  int bags_size = 0;

  status = regcomp(&regex, argv[1], REG_EXTENDED);
  if (status != 0) {
    regerror(status, &regex, error_buffer, error_buffer_size);
    printf("Error in regcomp, status %s\n", error_buffer);
    return 0;
  }

  status = regexec(&regex, argv[3], MAXGR, bags, 0);
  if (status != 0) {
    regerror(status, &regex, error_buffer, error_buffer_size);
    printf("Error in regexec, status %s\n", error_buffer);
    return 0;
  }

  for (int i = 1; i < MAXGR && bags[i].rm_so >= 0; ++i) {
    ++bags_size;
  }
  int start = bags[1].rm_so, end = bags[bags_size].rm_eo;

  // check invalid bag
  for (int i = 0; i < strlen(argv[2]); ++i) {
    if (argv[2][i] == '\\' && (i + 1) < strlen(argv[2])) {
      if ('0' < argv[2][i + 1] && argv[2][i + 1] <= '9') {
        if (argv[2][i + 1] - '0' > bags_size) {
          printf("Error, invalid bag number!\n");
          return 0;
        }
      }
    }
  }

  for (int i = 0; i < start; ++i) {
    printf("%c", argv[3][i]);
  }

  for (int i = 0; i < strlen(argv[2]); ++i) {
    if (argv[2][i] == '\\' && (i + 1) < strlen(argv[2])) {
      if (argv[2][i + 1] == '\\') {
        printf("\\");
      } else if ('0' < argv[2][i + 1] && argv[2][i + 1] <= '9') {
        if (argv[2][i + 1] - '0' <= bags_size) {
          int bag_num = argv[2][i + 1] - '0';
          for (int j = bags[bag_num].rm_so; j < bags[bag_num].rm_eo; ++j) {
            printf("%c", argv[3][j]);
          }
        }
      } else {
        printf("%c", argv[2][i + 1]);
      }
      ++i;
    } else {
      printf("%c", argv[2][i]);
    }
  }

  for (int i = end; i < strlen(argv[3]); ++i) {
    printf("%c", argv[3][i]);
  }
  printf("\n");

  regfree(&regex);
  return 0;
}

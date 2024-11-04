
#include "config.h"
#include <errno.h>
#include <rhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef READLINE
#include <readline/readline.h>
#endif

int main(int argc, char *argv[]) {

  char *command;
  size_t len = 0;
  ssize_t read;
  rhash_library_init();

#ifndef READLINE
  printf(">>>");
  while ((read = getline(&command, &len, stdin)) != -1) {
#else
  printf(">>>");
  while ((command = readline("")) != NULL) {
#endif

    int first_space_index = 0;
    for (; first_space_index < strlen(command); ++first_space_index) {
      if (command[first_space_index] == ' ')
        break;
    }

    unsigned hash_id;
    int print_flag;
    if (first_space_index == 3) {
      if (strncmp(command, "MD5", 3) == 0) {
        hash_id = RHASH_MD5;
        print_flag = RHPR_HEX;
      } else if (strncmp(command, "TTH", 3) == 0) {
        hash_id = RHASH_TTH;
        print_flag = RHPR_HEX;
      } else if (strncmp(command, "md5", 3) == 0) {
        hash_id = RHASH_MD5;
        print_flag = RHPR_BASE64;
      } else if (strncmp(command, "tth", 3) == 0) {
        hash_id = RHASH_TTH;
        print_flag = RHPR_BASE64;
      } else {
        fprintf(stderr, "Unknown command\n");
        printf(">>>");
        continue;
      }
    } else if (first_space_index == 4) {
      if (strncmp(command, "SHA1", 4) == 0) {
        hash_id = RHASH_SHA1;
        print_flag = RHPR_HEX;
      } else if (strncmp(command, "sha1", 4) == 0) {
        hash_id = RHASH_SHA1;
        print_flag = RHPR_BASE64;
      } else {
        fprintf(stderr, "Unknown command\n");
        printf(">>>");
        continue;
      }
    } else {
      fprintf(stderr, "Unknown command\n");
      printf(">>>");
      continue;
    }
    int start = first_space_index + 1;
    for (; start < strlen(command); ++start) {
      if (command[start] != ' ') {
        break;
      }
    }
    if (command[start] == ' ') {
      fprintf(stderr, "Not found argument\n");
      printf(">>>");
      continue;
    }
    int end = start;
    for (; end < strlen(command); ++end) {
      if (command[end] == ' ' || command[end] == '\n') {
        break;
      }
    }
    char msg[100];
    char digest[64];
    strncpy(msg, command + start, end - start);
    // printf("$%s$\n", msg);
    int res;
    if (command[start] == '\"') {
      res = rhash_msg(RHASH_SHA1, msg, strlen(msg), digest);
    } else {
      res = rhash_file(RHASH_TTH, msg, digest);
    }
    if (res < 0) {
      fprintf(stderr, "Error rhash\n");
      printf(">>>");
      continue;
    }

    char output[130];
    rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id),
                      (print_flag | RHPR_UPPERCASE));

    printf("%s\n", output);
    printf(">>>");
  }

  return 0;
}

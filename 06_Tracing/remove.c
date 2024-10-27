
#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*remove_type)(char *);

int remove(char *file_name) {
  if (strstr(file_name, "PROTECT") == NULL) {
    return ((remove_type)(dlsym(RTLD_NEXT, "remove")))(file_name);
  }
  return 0;
}

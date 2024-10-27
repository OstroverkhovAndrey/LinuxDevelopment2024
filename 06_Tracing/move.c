
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Invalid usage, correct usage:\n\t./move input output\n");
    return 0;
  }
  int in_file = open(argv[1], O_RDONLY, 0);
  if (in_file == -1) {
    fprintf(stderr, "Faild to open input file\n");
    return errno;
  }
  int out_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
  if (out_file == -1) {
    fprintf(stderr, "Faild to create or open output file\n");
    return errno;
  }

  int buf_size = 256, n, status;
  char buf[256];
  while ((n = read(in_file, buf, buf_size)) != 0) {
    if (n == -1) {
      fprintf(stderr, "Faild to reat from input file\n");
      return errno;
    }
    status = write(out_file, buf, n);
    if (status == -1) {
      fprintf(stderr, "Faild to write to output file\n");
      return errno;
    }
  }
  status = close(in_file);
  if (status == -1) {
    fprintf(stderr, "Faild to close input file\n");
    return errno;
  }
  status = close(out_file);
  if (status == -1) {
    fprintf(stderr, "Faild to close output file\n");
    return errno;
  }
  status = remove(argv[1]);
  if (status == -1) {
    fprintf(stderr, "Faild to delete input file\n");
    return errno;
  }
  return 0;
}

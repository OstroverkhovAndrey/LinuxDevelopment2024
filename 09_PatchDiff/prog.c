
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **create_labirint(int N, int M) {
  char **field = (char **)calloc(N, sizeof(char *));
  for (int i = 0; i < N; ++i) {
    field[i] = (char *)calloc(M, sizeof(char));
    for (int j = 0; j < M; ++j) {
      if (i % 2 && j % 2) {
        field[i][j] = '.';
      } else {
        field[i][j] = '#';
      }
    }
  }
  return field;
}

void free_labirint(char **field, int N, int M) {
  for (int i = 0; i < N; ++i) {
    free(field[i]);
  }
  free(field);
}

void print_labirint(char **field, int N, int M) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      printf("%c", field[i][j]);
    }
    printf("\n");
  }
}

struct Coord {
  int x;
  int y;
} typedef Coord;

int cheak_a11y(char **field, int N, int M) {
  Coord *stack = (Coord *)calloc(N * M, sizeof(Coord));
  int start = 0, end = 1;
  Coord temp;
  temp.x = 1;
  temp.y = 1;
  field[temp.x][temp.y] = ',';
  stack[0] = temp;

  while (start != end) {
    Coord curr = stack[start];
    start++;

    Coord temp1;
    temp1.x = curr.x - 2;
    temp1.y = curr.y;
    if (1 <= temp1.x && temp1.x <= N - 1 &&
        field[temp1.x + 1][temp1.y] == '.' && field[temp1.x][temp1.y] == '.') {
      stack[end] = temp1;
      end++;
      field[temp1.x][temp1.y] = ',';
    }

    temp1.x = curr.x + 2;
    temp1.y = curr.y;
    if (1 <= temp1.x && temp1.x <= N - 1 &&
        field[temp1.x - 1][temp1.y] == '.' && field[temp1.x][temp1.y] == '.') {
      stack[end] = temp1;
      end++;
      field[temp1.x][temp1.y] = ',';
    }

    temp1.x = curr.x;
    temp1.y = curr.y - 2;
    if (1 <= temp1.y && temp1.y <= M - 1 &&
        field[temp1.x][temp1.y + 1] == '.' && field[temp1.x][temp1.y] == '.') {
      stack[end] = temp1;
      end++;
      field[temp1.x][temp1.y] = ',';
    }

    temp1.x = curr.x;
    temp1.y = curr.y + 2;
    if (1 <= temp1.y && temp1.y <= M - 1 &&
        field[temp1.x][temp1.y - 1] == '.' && field[temp1.x][temp1.y] == '.') {
      stack[end] = temp1;
      end++;
      field[temp1.x][temp1.y] = ',';
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (i % 2 && j % 2) {
        field[i][j] = '.';
      }
    }
  }

  free(stack);
  // printf("visit: %i\n", start);
  if (start == ((N - 1) / 2) * ((M - 1) / 2)) {
    return 1;
  }
  return 0;
}

void create_way(char **field, int N, int M) {
  srand(time(NULL));
  while (1) {
    for (int i = 1; i < N - 1; ++i) {
      for (int j = 1; j < M - 1; ++j) {
        if ((i % 2 && !(j % 2)) || (!(i % 2) && j % 2)) {
          if (field[i][j] == '#' && (rand() % 100) > 90) {
            field[i][j] = '.';
          }
        }
      }
    }
    if (cheak_a11y(field, N, M)) {
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  int N = 13, M = 13;
  char **field = create_labirint(N, M);

  create_way(field, N, M);

  print_labirint(field, N, M);

  free_labirint(field, N, M);

  return 0;
}

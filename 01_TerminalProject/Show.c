
#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

// for test KEY_RIGHT
// aaaaaaaaaaaaaaaaaaaaaaaaaaaasssssssssssssssssssssssssssdddddddddddddddddddddddfffffffffffffffffffffffffffff1111111111111111111111111111222222222222222222222222222223333333333333333333333333334444444444444444444444444455

int min(int a, int b) {
  if (a < b)
    return a;
  return b;
}

int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Not found file name!\n");
    return -1;
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Cannot open file!\n");
    return 1;
  }

  int count_lines = 1;
  int max_len_line = 0;
  char **lines = (char **)calloc(count_lines, sizeof(char *));
  int cur_len = 0;
  lines[0] = (char *)calloc(cur_len, sizeof(char));
  while (1) {
    char c = fgetc(file);
    if (c == EOF) {
      break;
    } else {
      if (c != '\n') {
        ++cur_len;
        lines[count_lines - 1] =
            (char *)realloc(lines[count_lines - 1], cur_len * sizeof(char));
        lines[count_lines - 1][cur_len - 1] = c;
      } else {
        ++count_lines;
        lines = (char **)realloc(lines, count_lines * sizeof(char *));
        max_len_line = max(max_len_line, cur_len);
        cur_len = 0;
        lines[count_lines - 1] = (char *)calloc(cur_len, sizeof(char));
      }
    }
  }
  fclose(file);

  WINDOW *win;
  int c = 0;
  int cur_line = 0, cur_col = 0;

  setlocale(LC_ALL, "");
  initscr();
  noecho();
  cbreak();
  printw("File: %s; size: %i", argv[1], count_lines);
  refresh();

  int DX = 7, DY = 3;
  int win_size_y = LINES - 2 * DY, win_size_x = COLS - 2 * DX;
  win = newwin(win_size_y + 2, win_size_x + 2, DY, DX);
  keypad(win, TRUE);
  scrollok(win, TRUE);
  while (c != 27) {
    werase(win);
    for (int i = 0; i < win_size_y; ++i) {
      if (cur_line + i >= count_lines) {
        break;
      }
      int start_line = min(cur_col, strlen(lines[i + cur_line]));
      mvwprintw(win, i + DY - 1, 0, " %3d : %s\n", i + 1 + cur_line,
                lines[i + cur_line] + start_line);
    }
    box(win, 0, 0);
    wrefresh(win);
    c = wgetch(win);

    switch (c) {
    case KEY_UP:
      cur_line -= 1;
      cur_line = max(cur_line, 0);
      break;
    case KEY_RIGHT:
      if (cur_col + win_size_x - 10 < max_len_line) {
        ++cur_col;
      }
      break;
    case 32:
    case KEY_DOWN:
      cur_line += 1;
      cur_line = min(cur_line, count_lines - win_size_y);
      break;
    case KEY_LEFT:
      if (cur_col > 0) {
        --cur_col;
      }
      break;
    case KEY_NPAGE:
      cur_line += win_size_y;
      cur_line = min(cur_line, count_lines - win_size_y);
      break;
    case KEY_PPAGE:
      cur_line -= win_size_y;
      cur_line = max(cur_line, 0);
      break;
    }
  }

  delwin(win);
  endwin();

  for (int i = 0; i < count_lines; ++i) {
    free(lines[i]);
  }
  free(lines);
  return 0;
}

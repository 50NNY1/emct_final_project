#include <ncurses.h>
#include "Editor.h"

// Initializes the curses.h
void curses_init()
{
  initscr();
  cbreak();
  noecho();
}

string fn = "";

int main(int argc, char *argv[])
{
  // Initialize filename

  // if (argc > 1)
  // {
  //   fn = string(argv[1]);
  //   Editor ed(*win, fn);
  // }
  // else
  // {
  //   Editor ed(*win);
  // }

  curses_init();
  int window_width = COLS / 4;
  int window_height = LINES;
  WINDOW *window1 = newwin(window_height, window_width, 0, 0);
  WINDOW *window2 = newwin(window_height, window_width, 0, window_width);
  WINDOW *window3 = newwin(window_height, window_width, 0, window_width * 2);
  WINDOW *window4 = newwin(window_height, window_width, 0, window_width * 3);

  Editor ed(window1);

  box(window1, 0, 0);
  box(window2, 0, 0);
  box(window3, 0, 0);
  box(window4, 0, 0);

  refresh();
  wrefresh(window1);
  wrefresh(window2);
  wrefresh(window3);
  wrefresh(window4);

  while (ed.getMode() != 'x')
  {
    if (ed.upstatus)
      ed.updateStatus();
    ed.printStatusLine();
    ed.printBuff();
    int input = getch();
    ed.handleInput(input);
  }

  endwin();

  return 0;
}

// explain the difference between wmove and wprintw in ncurses
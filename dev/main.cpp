#include <ncurses.h>
#include "Editor.h"

// Initializes the curses.h
void curses_init()
{
  initscr();
  noecho();
  cbreak(); // Disable line buffering
  // keypad(stdscr, true);
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
  int height, width, start_y, start_x;
  getmaxyx(stdscr, height, width);
  start_y = 0;
  start_x = 0;
  WINDOW *win1 = newwin(height, width / 2, start_y, start_x);
  start_x = width / 2;
  WINDOW *win2 = newwin(height, width / 2, start_y, start_x);
  Editor ed(win1);
  box(win1, 0, 0);
  box(win2, 0, 0);
  while (ed.getMode() != 'x')
  {
    if (ed.upstatus)
      ed.updateStatus();
    ed.printStatusLine();
    ed.printBuff();
    int input = getch();
    ed.handleInput(input);
  }

  wrefresh(win1);
  wrefresh(win2);
  refresh();
  delwin(win1);
  delwin(win2);
  endwin();
  return 0;
}
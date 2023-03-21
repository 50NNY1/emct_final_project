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
  WINDOW *win = newwin(0, 0, 0, 0);
  Editor ed(*win);
  while (ed.getMode() != 'x')
  {
    if (ed.upstatus)
      ed.updateStatus();
    ed.printStatusLine();
    ed.printBuff();
    int input = getch();
    ed.handleInput(input);
  }

  refresh();
  endwin();
  return 0;
}
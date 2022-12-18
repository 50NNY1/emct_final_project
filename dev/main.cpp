#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "menu.h"

using namespace std;

int main()
{
  initscr();
  noecho();    // user cant draw to screen
  curs_set(0); // cursor invisible

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);
  WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
  box(win, 0, 0);

  Menu menus[3] = {
      Menu("Arr", 'a'),
      Menu("Scene", 's'),
      Menu("Pattern", 'd'),
  };

  MenuBar menubar(win, menus, 3);
  menubar.draw();

  char ch;
  while (ch = wgetch(win))
  {
    menubar.handleTrigger(ch);
    menubar.draw();
    endwin();
    return 0;
  }
}
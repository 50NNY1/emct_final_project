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

  if (!has_colors())
  {
    return -1;
  }
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
  box(win, 0, 0);

  string menu1[] = {"attributes", "open", "save", "exit"};
  string menu2[] = {"ch1", "ch2", "ch3", "ch4", "ch5", "ch6", "ch7", "ch8"};
  string menu3[] = {"test1", "test2"};
  Menu menus[3] = {
      Menu("Arr", 'a', menu1, 4),
      Menu("Scene", 's', menu2, 8),
      Menu("Pattern", 'd', menu3, 2),
  };

  MenuBar menubar(win, menus, 3);
  menubar.draw();

  char ch;
  while (ch = wgetch(win))
  {
    menubar.handleTrigger(ch);
    menubar.draw();
  }
  endwin();
  return 0;
}
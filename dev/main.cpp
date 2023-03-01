#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "menu.h"
#include "grid.h"
#include <panel.h>

int main()
{
  initscr();
  cbreak();
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

  WINDOW *my_wins[2];
  PANEL *my_panels[2];
  my_wins[0] = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);                   // menu bar window
  my_wins[1] = newwin((yMax / 2) + 1, (xMax / 2) + 1, (yMax / 4) - 1, xMax / 4); // grid window

  my_panels[0] = new_panel(my_wins[0]);
  my_panels[1] = new_panel(my_wins[1]);
  update_panels();
  std::string menu1[] = {"open", "save", "exit"};
  std::string menu2[] = {"ch1", "ch2", "ch3", "ch4", "ch5", "ch6", "ch7", "ch8"};
  std::string menu3[] = {"test1", "test2"};
  Menu menus[3] = {
      Menu("File", 'a', menu1, 3),
      Menu("Scene", 's', menu2, 8),
      Menu("Pattern", 'd', menu3, 2),
  };
  MenuBar menubar(my_wins[0], menus, 3);
  Grid grid;
  menubar.draw();
  int ch;
  while (ch = wgetch(my_wins[0]))
  {
    menubar.handleTrigger(ch);
    menubar.draw();
    grid.handle_input();
    grid.update();  
  }
  update_panels();

  endwin();
  return 0;
}
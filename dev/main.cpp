#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

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

  mvwprintw(win, 0, 2, "Arr");
  mvwprintw(win, 0, 7, "Scene");
  mvwprintw(win, 0, 14, "Pattern");

  char ch;
  while (ch = wgetch(win))
  {
    switch (ch)
    {
    case 'a':
      wattron(win, A_STANDOUT);
      mvwprintw(win, 0, 2, "Arr");
      wattroff(win, A_STANDOUT);
      mvwprintw(win, 0, 7, "Scene");
      mvwprintw(win, 0, 14, "Pattern");
      break;
    case 's':
      wattron(win, A_STANDOUT);
      mvwprintw(win, 0, 7, "Scene");
      wattroff(win, A_STANDOUT);
      mvwprintw(win, 0, 2, "Arr");
      mvwprintw(win, 0, 14, "Pattern");
      break;
    case 'd':
      wattron(win, A_STANDOUT);
      mvwprintw(win, 0, 14, "Pattern");
      wattroff(win, A_STANDOUT);
      mvwprintw(win, 0, 2, "Arr");
      mvwprintw(win, 0, 7, "Scene");
      break;
    default:
      mvwprintw(win, 0, 2, "Arr");
      mvwprintw(win, 0, 7, "Scene");
      mvwprintw(win, 0, 14, "Pattern");
      break;
    }
  }
  wgetch(win);

  endwin();
  return 0;
}
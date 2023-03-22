#include <ncurses.h>
#include <iostream>
#include <vector>
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
  int num_windows = 4;
  int window_width = COLS / 4;
  int window_height = LINES;
  std::vector<WINDOW *> windows(num_windows);
  for (int i = 0; i < num_windows; i++)
  {
    windows[i] = newwin(window_height, window_width, 0, i * window_width);
    box(windows[i], 0, 0);
    wrefresh(windows[i]);
  }
  std::vector<Editor> editors(num_windows);
  for (int i = 0; i < num_windows; i++)
  {
    editors[i] = Editor();
    editors[i].assignWindow(windows[i]);
  }

  while (true)
  {
    for (int i = 0; i < num_windows; i++)
    {
      Editor &ed = editors[i];
      WINDOW *win = windows[i];
      if (ed.getMode() != 'x')
      {
        if (ed.upstatus)
          ed.updateStatus();
        ed.printStatusLine();
        ed.printBuff();
        int input = wgetch(win);
        ed.handleInput(input);
      }
    }
    for (int i = 0; i < 4; i++)
    {
      wrefresh(windows[i]);
    }
  }

  endwin();
  return 0;
}
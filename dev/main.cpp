#include <ncurses.h>
#include <iostream>
#include <vector>
#include "Editor.h"
#include "popup.h"

#define ctrl(x) ((x)&0x1f)

// Initializes the curses.h
void curses_init()
{
  initscr();
  cbreak();
  noecho();
  start_color();
}

string fn = "";

int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  std::string ip = "127.0.0.1";
  std::string port = argv[1];
  std::string address[2] = {ip, port};

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
    editors[i].setAddress(address);
  }

  Popup popup(40, 10, 10, 5);

  int activeWindow = 0;
  init_pair(1, COLOR_BLACK, COLOR_GREEN);

  while (true)
  {
    for (int i = 0; i < editors.size(); i++)
    {
      if (i == activeWindow)
        editors[i].isActive(true);
      else
        editors[i].isActive(false);
    }
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
      }
    }
    for (int i = 0; i < 4; i++)
    {
      wrefresh(windows[i]);
    }

    int ch = getch();
    if (ch == ctrl('h'))
    {
      activeWindow = (activeWindow > 0) ? activeWindow - 1 : 0;
    }
    else if (ch == ctrl('l'))
    {
      activeWindow = (activeWindow < 3) ? activeWindow + 1 : 3;
    }
    else if (ch == ctrl('g'))
    {
      popup.toggle();
    }
    else if (ch == ctrl('g') && popup.isActive())
    {
      std::tuple<int, int, std::string> globParams = popup.getValues();
      popup.toggle();
    }
    if (ch != ctrl('l') && ch != ctrl('h') && ch != ctrl('g') && !popup.isActive())
    {
      editors[activeWindow].handleInput(ch);
    }
  }

  endwin();
  return 0;
}
#include <ncurses.h>
#include <iostream>
#include <signal.h>
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

// makes sure ncurses is properly exited on ctrl-c
void sigint_handler(int sig)
{
  endwin();
  signal(sig, SIG_DFL);
  raise(sig);
}

string fn = "";

int main(int argc, char *argv[])
{
  std::cout << "Please launch with desired port number as arguement and then no. of 1UP instances." << std::endl;
  if (argc != 3)
    return 1;

  std::string ip = "127.0.0.1";
  std::string port = argv[1];
  int num_instances = atoi(argv[2]);
  std::string address[2] = {ip, port};

  curses_init();
  int num_windows = num_instances;
  int window_width = COLS / num_instances;
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
    editors[i].assignInstance(i + 1);
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
    for (int i = 0; i < num_windows; i++)
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
      activeWindow = (activeWindow < num_instances - 1) ? activeWindow + 1 : num_instances - 1;
    }
    else if (ch == ctrl('g'))
    {
      popup.toggle();
    }
    else if (ch == ctrl('g') && popup.isActive())
    {
      std::vector<int> globParams = popup.getValues();
      address[1] = globParams[1];
      popup.toggle();
    }
    if (ch != ctrl('l') && ch != ctrl('h') && ch != ctrl('g') && !popup.isActive())
    {
      editors[activeWindow].handleInput(ch);
    }
  }

  signal(SIGINT, sigint_handler);
  for (int i = 0; i < num_windows; i++)
  {
    delwin(windows[i]);
  }
  endwin();
  return 0;
}
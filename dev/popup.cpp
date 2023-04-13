#include "popup.h"
#include <ncurses.h>
#include <string>
#include <vector>

Popup::Popup(int width, int height, int x, int y)
{
    // Create the window
    win = newwin(height, width, y, x);

    // Set the window attributes
    box(win, 0, 0);
    keypad(win, true);

    // Make the window a popup
    init_colors();
    wbkgd(win, COLOR_PAIR(1));
    wattron(win, A_BOLD);
    wrefresh(win);

    ison = false;
}

void Popup::init_colors()
{
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_GREEN);
    }
}

void Popup::show(const char *message)
{
    // Display the message in the window
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(1));
    mvwprintw(win, 1, 1, message);

    // Refresh the window
    wrefresh(win);
}

void Popup::hide()
{
    // Hide the window
    wbkgd(win, COLOR_PAIR(0));
    wclear(win);
    wrefresh(win);
}

void Popup::toggle()
{
    if (!ison)
    {
        show("Hello World");
        ison = true;
    }
    else
    {
        hide();
        ison = false;
    }
}

bool Popup::isActive()
{
    return ison;
}
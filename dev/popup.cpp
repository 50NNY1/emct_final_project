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
    werase(win);
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(1));
    int row = 1;
    mvwprintw(win, row, 1, "BPM: ");
    row++;
    wattron(win, A_UNDERLINE);
    mvwhline(win, row, 1, ' ', 10);
    wattroff(win, A_UNDERLINE);
    wrefresh(win);

    char bpm_str[10];
    echo();
    mvwgetnstr(win, row, 2, bpm_str, 10);
    noecho();

    int bpm = atoi(bpm_str);
    if (bpm < 0)
    {
        bpm = 0;
    }
    else if (bpm > 200)
    {
        bpm = 200;
    }

    row += 2;

    // Display the port number input box
    mvwprintw(win, row, 1, "Port number:");
    row++;
    wattron(win, A_UNDERLINE);
    mvwhline(win, row, 1, ' ', 15);
    wattroff(win, A_UNDERLINE);
    wrefresh(win);

    // Get user input for port number
    char port_str[10];
    echo();
    mvwgetnstr(win, row, 2, port_str, 10);
    noecho();

    int port = atoi(port_str);
    if (port < 0)
    {
        port = 0;
    }
    else if (port > 10000)
    {
        port = 10000;
    }

    row += 2;

    // Display the IP address input box
    mvwprintw(win, row, 1, "IP address:");
    row++;
    wattron(win, A_UNDERLINE);
    mvwhline(win, row, 1, ' ', 20);
    wattroff(win, A_UNDERLINE);
    wrefresh(win);

    // Get user input for IP address
    char ip_str[20];
    echo();
    mvwgetnstr(win, row, 2, ip_str, 20);
    noecho();

    std::string ip(ip_str);

    // Display the input values
    werase(win);
    mvwprintw(win, 1, 1, "BPM: %d", bpm);
    mvwprintw(win, 2, 1, "Port number: %d", port);
    mvwprintw(win, 3, 1, "IP address: %s", ip_str);
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

std::tuple<int, int, std::string> Popup::getValues()
{
    return std::make_tuple(bpm, port, ip);
}
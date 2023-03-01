#include <ncurses.h>

int main()
{
    // Initialize ncurses
    initscr();

    // Disable line buffering and echoing of keystrokes
    cbreak();
    noecho();

    // Create four windows
    int window_width = COLS / 4;
    int window_height = LINES;
    WINDOW *window1 = newwin(window_height, window_width, 0, 0);
    WINDOW *window2 = newwin(window_height, window_width, 0, window_width);
    WINDOW *window3 = newwin(window_height, window_width, 0, window_width * 2);
    WINDOW *window4 = newwin(window_height, window_width, 0, window_width * 3);

    // Write text in each window
    mvwprintw(window1, 1, 1, "This is window 1");
    mvwprintw(window2, 1, 1, "This is window 2");
    mvwprintw(window3, 1, 1, "This is window 3");
    mvwprintw(window4, 1, 1, "This is window 4");

    // Create a box outline around all the windows
    box(window1, 0, 0);
    box(window2, 0, 0);
    box(window3, 0, 0);
    box(window4, 0, 0);

    // Refresh all the windows
    refresh();
    wrefresh(window1);
    wrefresh(window2);
    wrefresh(window3);
    wrefresh(window4);

    // Wait for a key press
    getch();

    // Clean up ncurses
    endwin();

    return 0;
}

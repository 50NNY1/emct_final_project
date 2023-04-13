#ifndef POPUP_H
#define POPUP_H

#include <ncurses.h>
#include <string>
#include <vector>
class Popup
{
public:
    Popup(int width, int height, int x, int y);
    void init_colors();
    bool isActive();
    void show(const char *message);
    void hide();
    void toggle();

private:
    WINDOW *win;
    bool ison;
};

#endif
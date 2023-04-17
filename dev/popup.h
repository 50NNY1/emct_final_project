#ifndef POPUP_H
#define POPUP_H

#include <ncurses.h>
#include <string>
#include <vector>
class Popup
{
public:
    Popup(int width, int height, int x, int y);
    bool isActive();
    void toggle();
    std::tuple<int, int, std::string> getValues();

private:
    void init_colors();
    void show(const char *message);
    void hide();
    WINDOW *win;
    bool ison;
    int bpm;
    int port;
    std::string ip;
};

#endif
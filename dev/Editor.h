#ifndef EDITOR_H
#define EDITOR_H

#include "Buffer.h"
#include <ncurses.h>

#define CED_TITLE "1UP"
#define CED_VERSION "pre-alpha 0."

class Editor
{
private:
    int x, y;
    int winx;
    int lowerbound;
    char mode;
    bool raiseflag;
    Buffer *buff;
    string status;
    string cmd;
    string filename;
    bool active;
    string tos(int);
    WINDOW *win;
    bool execCmd();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void deleteLine();
    void deleteLine(int i);

    void sendMsg();
    void saveFile();

public:
    bool upstatus;

    Editor(WINDOW *win_);
    Editor();
    char getMode()
    {
        return mode;
    }

    void handleInput(int);
    void assignWindow(WINDOW *win_) { win = win_; }
    void printBuff();
    void printStatusLine();
    void updateStatus();
    void isActive(bool _active);
};

#endif
#ifndef EDITOR_H
#define EDITOR_H

#include "Buffer.h"

#include <ncurses.h>

#define CED_TITLE "ceditor"
#define CED_VERSION "v0.1.0 test"

class Editor
{
private:
    int x, y;
    int lowerbound;
    char mode;
    bool raiseflag;
    Buffer *buff;
    string status;
    string cmd;
    string filename;
    string tos(int);
    WINDOW *win;
    bool execCmd();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void deleteLine();
    void deleteLine(int i);

    void saveFile();

public:
    bool upstatus;

    Editor(WINDOW *win_);
    // Editor(WINDOW &win_, string);

    char getMode() { return mode; }

    void handleInput(int);
    void printBuff();
    void printStatusLine();
    void updateStatus();
};

#endif
#ifndef EDITOR_H
#define EDITOR_H

#include "Buffer.h"
#include "OSC.h"

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
    std::string address[2];
    Buffer *buff;
    string status;
    string cmd;
    string filename;
    bool active;
    WINDOW *win;
    std::string ctrl_k_str;
    int loop_toggle;
    int instancenum;
    bool isLooping;

    string tos(int);
    bool execCmd();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void deleteLine();
    void deleteLine(int i);
    void wait(int duration);
    void saveFile();

public:
    bool upstatus;

    Editor(WINDOW *win_);
    Editor();
    char getMode()
    {
        return mode;
    }
    void sendMsg();
    void runSeq();
    void handleInput(int);
    void assignWindow(WINDOW *win_) { win = win_; }
    void assignInstance(int instancenum_) { instancenum = instancenum_; }
    void printBuff();
    void printStatusLine();
    void updateStatus();
    void isActive(bool _active);
    void setAddress(std::string _address[]);
};

#endif
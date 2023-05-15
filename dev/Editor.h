/*code adapated from the Editor class in:
NCURSES Terminal Text Editor Tutorial Part 1 - 4 (2015) Cheuk’s Blog. Available at: https://cheuksblog.ca/2015-02-01-ncurses-editor-tutorial-01/ (Accessed: 1 March 2023).
*/
#ifndef EDITOR_H
#define EDITOR_H

#include "Buffer.h"
#include "OSC.h"

#include <ncurses.h>

#define CED_TITLE "1UP"
#define CED_VERSION "alpha 0.1"

class Editor
{
private:
    int loopBegin = 0;
    int loopEnd = 0;
    int x, y;
    int winx;
    int lowerbound;
    char mode;
    bool raiseflag;
    std::string address[2];
    Buffer *buff;
    string status;
    string cmd;
    int jargon_toggle;
    string filename;
    bool active;
    float beat_dur;
    WINDOW *win;
    std::string ctrl_k_str;
    int loop_toggle;
    int instancenum;
    bool isLooping;
    int bpm;
    std::vector<OSC *> oscs;

    string tos(int);
    bool execCmd();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void deleteLine();
    void deleteLine(int i);
    void saveFile();

    void jargonToggle() { jargon_toggle++; }

public:
    bool upstatus;

    Editor(WINDOW *win_);
    Editor();
    char getMode()
    {
        return mode;
    }
    void sendMsg();
    void runSeq(int iteration, bool isToPlay, float beat_dur, OSC &osc);
    void runSeq_thread();
    void handleInput(int);
    void assignWindow(WINDOW *win_) { win = win_; }
    void assignInstance(int instancenum_) { instancenum = instancenum_; }
    void assignTime(std::vector<int> time_);
    void printBuff();
    void printStatusLine();
    void updateStatus();
    void isActive(bool _active);
    void setAddress(std::string _address[]);
};

#endif
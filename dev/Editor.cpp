#include "Editor.h"

#include <fstream>
#include <iostream>
#include <sstream>

#define ctrl(x) ((x)&0x1f)

Editor::Editor()
{
    x = 0;
    y = 0;
    winx = 0;
    mode = 'n';
    cmd = "";
    upstatus = true;
    raiseflag = false;
    status = "Normal Mode";
    lowerbound = 0;
    filename = "";
    buff = new Buffer();
    buff->appendLine("");
    active = false;
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
}
Editor::Editor(WINDOW *win_) : win(win_)
{
    x = 0;
    y = 0;
    winx = getbegx(win);
    mode = 'n';
    cmd = "";
    upstatus = true;
    raiseflag = false;
    status = "Normal Mode";
    lowerbound = 0;
    filename = "";
    buff = new Buffer();
    buff->appendLine("");
}

void Editor::updateStatus()
{
    switch (mode)
    {
    case 'n':
        if (cmd.empty())
            status = string(CED_TITLE) + " " + string(CED_VERSION);
        else
            status = cmd;
        break;
    case 'i':
        status = "Insert Mode";
        break;
    case 'x':
        status = "Exiting";
        break;
    }
    status += "\tCOL: " + tos(x) + "\tROW: " + tos(lowerbound);
}

void Editor::handleInput(int c)
{
    upstatus = true;
    switch (mode)
    {
    case 'n':
        switch (c)
        {
        case KEY_LEFT:
            moveLeft();
            break;
        case KEY_RIGHT:
            moveRight();
            break;
        case KEY_UP:
            moveUp();
            break;
        case KEY_DOWN:
            moveDown();
            break;
        case KEY_ENTER:
        case 10:
            // Execute the command
            execCmd();
            break;
        case 27:
            // Escape/Alt key
            // clears command
            cmd.clear();
            break;
        case 127:
        case KEY_BACKSPACE:
        case KEY_DC:
            // Removes last character
            if (!cmd.empty())
                cmd.erase(cmd.length() - 1, 1);
            break;
        default:
            // Add character to command
            cmd += string(1, char(c));
            break;
        }
        break;
    case 'i':
        switch (c)
        {
        case 27:
            // Escape/Alt key
            mode = 'n';
            break;
        case 127:
        case KEY_BACKSPACE:
            // The Backspace
            if (x == 0 && y > 0)
            {
                x = buff->lines[y - 1].length();
                // Bring line down
                buff->lines[y - 1] += buff->lines[y];
                // Delete the line
                deleteLine();
                moveUp();
            }
            else if (x > 0)
            {
                buff->lines[y].erase(--x, 1);
            }
            break;
        case KEY_DC:
            // The Delete key
            if (x == buff->lines[y].length() && y != buff->lines.size() - 1)
            {
                // Bring line down
                buff->lines[y] += buff->lines[y + 1];
                // Delete the line
                deleteLine(y + 1);
            }
            else
            {
                buff->lines[y].erase(x, 1);
            }
            break;
        case KEY_LEFT:
            moveLeft();
            break;
        case KEY_RIGHT:
            moveRight();
            break;
        case KEY_UP:
            moveUp();
            break;
        case KEY_DOWN:
            moveDown();
            break;
        case KEY_ENTER:
        case 10:
            // Bring rest of line down
            if (x < buff->lines[y + lowerbound].length() - 1)
            {
                // Put rest of line on new line
                buff->insertLine(buff->lines[y + lowerbound].substr(x, buff->lines[y + lowerbound].length() - x), y + 1);
                // Remove that part of the line
                buff->lines[y + lowerbound].erase(x, buff->lines[y + lowerbound].length() - x);
            }
            else
                buff->insertLine("", y + lowerbound + 1);
            moveDown();
            break;
        case KEY_BTAB:
        case KEY_CTAB:
        case KEY_STAB:
        case KEY_CATAB:
        case ctrl('k'):
            sendMsg();
            break;
        case 9:
            // The tab
            buff->lines[y + lowerbound].insert(x, 4, ' ');
            x += 4;
            break;
        default:
            buff->lines[y + lowerbound].insert(x, 1, char(c));
            x++;
            break;
        }
        break;
    default:;
    }
}

void Editor::sendMsg()
{
    int lc = 0; // Line count
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    for (int i = lowerbound; lc < LINES - 1; i++)
    {
        if (i >= buff->lines.size())
        {
        }
        else
        {
            if (i == y + lowerbound)
                wattron(win, COLOR_PAIR(1));
            mvwprintw(win, lc, 0, buff->lines[i].c_str());
            if (i == y + lowerbound)
                wattroff(win, COLOR_PAIR(1));
        }
        wclrtoeol(win);
        lc++;
    }
    wmove(win, y, x);
    wrefresh(win);
}
void Editor::deleteLine()
{
    buff->removeLine(y);
}

void Editor::deleteLine(int i)
{
    buff->removeLine(i);
}

void Editor::moveLeft()
{
    if (x - 1 >= 0)
    {
        x--;
        wmove(win, y, x);
    }
    wrefresh(win);
}

void Editor::moveRight()
{
    if (x + 1 < COLS && x + 1 <= buff->lines[y].length())
    {
        x++;
        wmove(win, y, x);
    }
    wrefresh(win);
}

void Editor::moveUp()
{
    if (y - 1 >= 0)
    {
        y--;
    }
    else if (y - 1 < 0 && lowerbound > 0)
    {
        lowerbound--;
    }
    if (x >= buff->lines[y].length())
        x = buff->lines[y].length();
    wmove(win, y, x);
    wrefresh(win);
}

void Editor::moveDown()
{
    if (y + 1 < LINES - 1 && y + 1 < buff->lines.size())
    {
        y++;
    }
    else if (lowerbound + y < buff->lines.size())
    {
        raiseflag = true;
        lowerbound++;
    }
    if (x >= buff->lines[y].length())
        x = buff->lines[y].length();
    wmove(win, y, x);
    wrefresh(win);
}

void Editor::printBuff()
{
    int lc = 0; // Line count
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    for (int i = lowerbound; lc < LINES - 1; i++)
    {
        if (i >= buff->lines.size())
        {
        }
        else
        {
            mvwprintw(win, lc, 0, buff->lines[i].c_str());
        }
        wclrtoeol(win);
        lc++;
    }
    wmove(win, y, x);
    wrefresh(win);
}

void Editor::printStatusLine()
{
    if (raiseflag)
        wattron(win, A_BOLD);
    wattron(win, A_REVERSE);
    if (active)
        wattron(win, COLOR_PAIR(1));
    mvwprintw(win, LINES - 1, 0, status.c_str());
    wclrtoeol(win);
    if (raiseflag)
        wattroff(win, A_BOLD);
    wattroff(win, A_REVERSE);
    if (active)
        wattroff(win, COLOR_PAIR(1));
    wrefresh(win);
}

void Editor::saveFile()
{
    if (filename == "")
    {
        // Set filename to untitled
        filename = "untitled";
    }

    ofstream f(filename.c_str());
    if (f.is_open())
    {
        for (int i = 0; i < buff->lines.size(); i++)
        {
            f << buff->lines[i] << endl;
        }
        status = "Saved to file!";
    }
    else
    {
        status = "Error: Cannot open file for writing!";
    }
    f.close();
}

string Editor::tos(int n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

bool Editor::execCmd()
{
    if (cmd == "i")
        mode = 'i';
    else if (cmd == "x")
        mode = 'x';
    else if (cmd == "s")
    {
        upstatus = false;
        saveFile();
    }

    cmd = "";    // Reset command buffer
    return true; // Returns if command has executed successfully
}

void Editor::isActive(bool _active)
{
    active = _active;
}
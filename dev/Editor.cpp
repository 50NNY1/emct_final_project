#include "Editor.h"
#include "Euc.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <unordered_map>
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
    int ctrl_k = ctrl('k');
    std::string ctrl_k_str = "^" + std::to_string(ctrl_k + 64);
    loop_toggle = 0;
    bpm = 120;
    beat_dur = 60.0 / bpm;
}
Editor::Editor(WINDOW *win_) : win(win_)
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
    int ctrl_k = ctrl('k');
    std::string ctrl_k_str = "^" + std::to_string(ctrl_k + 64);
    loop_toggle = 0;
    bpm = 120;
    beat_dur = 60.0 / bpm;
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
    status += "\tCOL: " + tos(x) + "\tROW: " + tos(y);
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
    if (buff->lines[y][0] == 'm')
    {
        OSC osc(address, instancenum);
        std::tuple<int, float, float> curLineParsed = osc.parseMono(buff->lines[y]);
        std::thread oscT1(&OSC::sendMonoNote, osc, std::get<0>(curLineParsed),
                          std::get<1>(curLineParsed),
                          std::get<2>(curLineParsed));
        oscT1.detach();
    }
    else if (buff->lines[y][0] == 'p')
    {
        OSC osc(address, instancenum);
        std::tuple<std::vector<int>, std::vector<float>, float>
            curLineParsed = osc.parsePoly(buff->lines[y]);
        std::thread oscT2(&OSC::sendPoly, osc, std::get<0>(curLineParsed),
                          std::get<1>(curLineParsed),
                          std::get<2>(curLineParsed));
        oscT2.detach();
    }
    else if (buff->lines[y][0] == 'o')
    {
        OSC osc(address, instancenum);
        std::tuple<std::unordered_map<char, int>, std::vector<float>> curLineParsed = osc.parseMacro(buff->lines[y]);
        std::thread oscT3(&OSC::sendMacro, osc, std::get<0>(curLineParsed),
                          std::get<1>(curLineParsed));
        oscT3.detach();
    }
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
    else if (cmd == "K")
    {
        sendMsg();
    }
    else if (cmd == "[D")
    {
        moveLeft();
    }
    else if (cmd == "[C")
    {
        moveRight();
    }
    else if (cmd == "[A")
    {
        moveUp();
    }
    else if (cmd == "[B")
    {
        moveDown();
    }
    else if (cmd == "k")
    {

        std::thread seq_thread(&Editor::runSeq_thread, this);
        seq_thread.detach();
    }
    else if (cmd == "t")
    {
        OSC osc(address, instancenum);
        osc.test(buff->lines[y]);
    }
    else if (cmd[0] == 'b')
    {
        bpm = std::stoi(cmd.substr(1));
        beat_dur = 60.0 / bpm;
    }
    else
    {
        status = "Error: Command not found!";
        return false;
    }
    cmd = "";    // Reset command buffer
    return true; // Returns if command has executed successfully
}

void Editor::isActive(bool _active)
{
    active = _active;
}

void Editor::runSeq(int iteration, bool isToPlay, float beat_dur)
{

    auto start = std::chrono::steady_clock::now(); // start the timer
    OSC osc(address, instancenum);
    if (isToPlay)
    {
        if (buff->lines[iteration][0] == 'm')
        {
            std::tuple<int, float, float> curLineParsed = osc.parseMono(buff->lines[iteration]);
            osc.sendMonoNote(std::get<0>(curLineParsed),
                             std::get<1>(curLineParsed),
                             std::get<2>(curLineParsed));
        }
        else if (buff->lines[iteration][0] == 'p')
        {
            std::tuple<std::vector<int>, std::vector<float>, float> curLineParsed = osc.parsePoly(buff->lines[iteration]);
            osc.sendPoly(std::get<0>(curLineParsed),
                         std::get<1>(curLineParsed),
                         std::get<2>(curLineParsed));
        }
        else if (buff->lines[iteration][0] == 'o')
        {
            std::tuple<std::unordered_map<char, int>, std::vector<float>> curLineParsed = osc.parseMacro(buff->lines[iteration]);
            osc.sendMacro(std::get<0>(curLineParsed), std::get<1>(curLineParsed));
        }
        else if (buff->lines[iteration][0] == 'w')
        {
            int exclamationIndex = buff->lines[iteration].find('!');
            string numberString = buff->lines[iteration].substr(exclamationIndex + 1);
            int number = stoi(numberString);
            osc.wait(number);
        }
    }
    auto elapsed = std::chrono::steady_clock::now() - start;
    while (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() < beat_dur)
    {
        elapsed = std::chrono::steady_clock::now() - start;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() >= beat_dur)
        {
            break;
        }
    }
}

void Editor::setAddress(std::string _address[])
{
    address[0] = _address[0];
    address[1] = _address[1];
}

void Editor::runSeq_thread()
{
    loop_toggle++;
    if (buff->lines.size() > 1 |
            buff->lines.size() > 1 &&
        buff->lines[0] != "")
    {
        for (int i = y; i >= 0; i--)
        {
            if (buff->lines[i][0] == '(')
            {
                loopBegin = i;
                break;
            }
        }
        for (int i = loopBegin; i < buff->lines.size(); i++)
        {
            if (buff->lines[i][0] == ')')
            {
                loopEnd = i;
                break;
            }
        }

        // prepare euclidean sequence
        int euc_subdiv = std::stoi(buff->lines[loopEnd].substr(2));
        int euc_steps = (loopEnd - loopBegin) - 2;

        EuclideanSequence seq(euc_steps, euc_subdiv, bpm);
        std::vector<int> eucseq = seq.generateSequence();
        std::vector<float> eucseq_dur = seq.generateDurations();

        for (int i = loopBegin; i <= loopEnd; i++)
        {
            if (loop_toggle % 2 == 1)
            {
                if (buff->lines[i][0] != '#')
                {
                    std::thread loopThread(&Editor::runSeq, this, i, eucseq[i], eucseq_dur[i]);
                    loopThread.join();
                }
            }
            if (i == loopEnd)
                i = loopBegin;
        }
    }
}
/*full citation:
NCURSES Terminal Text Editor Tutorial Part 1 - 4 (2015) Cheuk’s Blog. Available at: https://cheuksblog.ca/2015-02-01-ncurses-editor-tutorial-01/ (Accessed: 1 March 2023).
*/
#ifndef BUFFER_H
#define BUFFER_H

#include <ncurses.h>
#include <vector>
#include <string>

using namespace std;

class Buffer
{
private:
public:
    Buffer();

    vector<string> lines;

    void insertLine(string, int);
    void appendLine(string);
    void removeLine(int);
    string remTabs(string);
};

#endif
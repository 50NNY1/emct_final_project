#include "Buffer.h"

Buffer::Buffer() {}

string Buffer::remTabs(string line)
{
    int tab = line.find("\t");
    if(tab == line.npos)
        return line;
    else
        return remTabs(line.replace(tab, 1, "    "));
}

void Buffer::insertLine(string line, int n)
{
    line = remTabs(line);                   // Conversion (happens every time)
    lines.insert(lines.begin()+n, line);
}

void Buffer::appendLine(string line)
{
    line = remTabs(line);
    lines.push_back(line);
}

void Buffer::removeLine(int n)
{
    lines.erase(lines.begin()+n);
}


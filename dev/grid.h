#include <curses.h>
#include <string>

#ifndef _GRID_H_
#define _GRID_H_

class Grid
{
public:
    Grid(WINDOW *win, int cells_x, int cells_y)
    {
        this->win = win;
        this->cells_x = cells_x;
        this->cells_y = cells_y;
    };
    void draw()
    {
        int yMax, xMax;
        getmaxyx(win, yMax, xMax);
        cell_width = xMax / cells_x;
        cell_height = yMax / cells_y;

        for (int i = 0; i < cells_x; i++)
        {
            for (int j = 0; j < cells_y; j++)
            {
                mvwhline(win, i * cell_height, j * cell_width, ACS_HLINE, cell_width * cells_x);
                mvwvline(win, j * cell_height, i * cell_width, ACS_VLINE, cell_height * cells_y);
            }
        }
        wrefresh(win);
    }

private:
    WINDOW *win;
    int cells_x;
    int cells_y;
    int cell_width;
    int cell_height;
};

#endif
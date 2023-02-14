#include <curses.h>
#include <string>

#ifndef _GRID_H_
#define _GRID_H_

class Grid
{
public:
    Grid(WINDOW *win, int rows, int cols) : rows(rows), cols(cols)
    {
        this->win = win;
        grid = new std::string *[rows];
        x = 0;
        y = 0;
        for (int i = 0; i < rows; i++)
        {
            grid[i] = new std::string[cols];
            for (int j = 0; j < cols; j++)
            {
                grid[i][j] = " ";
            }
        }
    };
    ~Grid()
    {
        // Deallocate the 2D array
        for (int i = 0; i < rows; i++)
        {
            delete[] grid[i];
        }
        delete[] grid;
    }
    void handleTrigger(int ch)
    {
        clear();
        print_grid();
        move(y, x * 3);
        switch (ch)
        {
        case KEY_UP:
            if (y > 0)
                y--;
            break;
        case KEY_DOWN:
            if (y < rows - 1)
                y++;
            break;
        case KEY_LEFT:
            if (x > 0)
                x--;
            break;
        case KEY_RIGHT:
            if (x < cols - 1)
                x++;
            break;
        case 10: // enter
            mvwprintw(win, rows + 2, 0, "Enter value for cell [%d, %d]: ", y, x);
            char buffer[1024];
            echo();
            getstr(buffer);
            noecho();
            grid[y][x] = buffer;
            break;
        case 27: // escape
            endwin();
        default:
            break;
        }
    }

    void print_grid()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                wprintw(win, "%s", grid[i][j].c_str());
            }
            wprintw(win, "\n");
        }
    }

private:
    WINDOW *win;
    int rows, cols;
    std::string **grid;
    bool edit_mode;
    int x, y;
};

#endif
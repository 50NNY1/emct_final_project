#include <ncurses.h>
#include <string>
#include <panel.h>

const int ROWS = 10;
const int COLUMNS = 10;

class Grid
{
public:
    GridPanel()
    {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, true);
        panel_ = new_panel(stdscr);
        init_grid();
        update();
    }

    ~GridPanel()
    {
        del_panel(panel_);
        endwin();
    }

    void update()
    {
        update_panels();
        doupdate();
    }

    void move(int x, int y)
    {
        x_ = x;
        y_ = y;
        move_panel(panel_, y_, x_ * 3);
        update();
    }

    void handle_input()
    {
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            if (y_ > 0)
                y_--;
            break;
        case KEY_DOWN:
            if (y_ < ROWS - 1)
                y_++;
            break;
        case KEY_LEFT:
            if (x_ > 0)
                x_--;
            break;
        case KEY_RIGHT:
            if (x_ < COLUMNS - 1)
                x_++;
            break;
        case 10: // enter
            mvprintw(ROWS + 2, 0, "Enter value for cell [%d, %d]: ", y_, x_);
            char buffer[1024];
            echo();
            getstr(buffer);
            noecho();
            grid_[y_][x_] = buffer;
            break;
        case 27: // escape
            endwin();
            exit(0);
            break;
        default:
            break;
        }
    }

private:
    PANEL *panel_;
    std::string grid_[ROWS][COLUMNS];
    int x_ = 0, y_ = 0;

    void init_grid()
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                grid_[i][j] = " ";
            }
        }
    }

    void print_grid()
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                mvprintw(i, j * 3, "[%s]", grid_[i][j].c_str());
            }
        }
    }
};
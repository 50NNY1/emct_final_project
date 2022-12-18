#include <curses.h>
#include <string>

#ifndef _MENU_H_
#define _MENU_H_

class Menu
{
public:
    Menu(std::string text, char trigger)
    {
        this->text = text;
        this->trigger = trigger;
    };

    int start_x;
    std::string text;
    char trigger;
};

class MenuBar
{
public:
    MenuBar(WINDOW *win, Menu *menus, int num_menus)
    {
        this->win = win;
        this->menus = menus;
        this->num_menus = num_menus;
        this->selected = -1;

        int currentPos = 2;
        for (int i = 0; i < num_menus; i++)
        {
            this->menus[i].start_x = currentPos;
            currentPos += this->menus[i].text.length() + 1;
        }
    };

    void draw()
    {
        for (int i = 0; i < num_menus; i++)
        {
            if (selected == i)
            {
                wattron(win, A_STANDOUT);
            }
            mvwprintw(win, 0, menus[i].start_x, menus[i].text.c_str());
            wattroff(win, A_STANDOUT);
        }
    }

    void handleTrigger(char trigger)
    {
        for (int i = 0; i < num_menus; i++)
        {
            if (trigger == this->menus[i].trigger)
            {
                selected = i;
            }
        }
    }

    WINDOW *win;
    Menu *menus;
    int num_menus;
    int selected;
};

#endif
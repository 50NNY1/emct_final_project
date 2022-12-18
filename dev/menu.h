#include <curses.h>
#include <string>

#ifndef _MENU_H_
#define _MENU_H_

class Menu
{
public:
    Menu(std::string text, char trigger, std::string *items, int num_items)
    {
        this->text = text;
        this->trigger = trigger;
        this->items = items;
        this->num_items = num_items;
        this->selected = 0;
    };

    int start_x;
    std::string text;
    char trigger;

    std::string *items;
    int num_items;
    int selected;

    void selectNextItem()
    {
        selected++;
        if (selected >= num_items)
        {
            selected = 0;
        }
    }

    void selectPrevItem()
    {
        selected--;
        if (selected < 0)
        {
            selected = num_items - 1;
        }
    }
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

        int yMax, xMax, yBeg, xBeg;
        getmaxyx(win, yMax, xMax);
        getbegyx(win, yBeg, xBeg);
        menuwin = newwin(yMax - 2, xMax - 2, yBeg + 1, xBeg + 1);
        keypad(menuwin, true);
        wrefresh(menuwin);

        int currentPos = 2;
        for (int i = 0; i < num_menus; i++)
        {
            this->menus[i].start_x = currentPos;
            currentPos += this->menus[i].text.length() + 1;
        }
    };

    void reset()
    {
        for (int i = 0; i < num_menus; i++)
        {
            mvwprintw(win, 0, menus[i].start_x, menus[i].text.c_str());
        }
        wrefresh(win);
    }
    void draw()
    {
        for (int i = 0; i < num_menus; i++)
        {
            drawMenu(menus[i], selected == i);
        }
        selected = -1;
    }

    void drawMenu(Menu menu, bool is_selected)
    {
        int start_x = menu.start_x;
        std::string text = menu.text;
        if (is_selected)
            wattron(win, A_STANDOUT);
        mvwprintw(win, 0, start_x, text.c_str());
        wattroff(win, A_STANDOUT);
        wrefresh(win);

        int ch;
        drawMenuItems(menu);
        wrefresh(menuwin);
        while (is_selected && (ch = wgetch(menuwin)))
        {
            switch (ch)
            {
            case KEY_DOWN:
                menu.selectNextItem();
                break;
            case KEY_UP:
                menu.selectPrevItem();
                break;
            default:
                is_selected = false;
                break;
            }
            drawMenuItems(menu);
        }
        werase(menuwin);
        wrefresh(menuwin);
        reset();
    }

    void drawMenuItems(Menu menu)
    {
        int ymax, xmax;
        getmaxyx(menuwin, ymax, xmax);
        for (int i = 0; i < menu.num_items; i++)
        {
            mvwprintw(menuwin, i, 0, menu.items[i].c_str());
            if (menu.selected == i)
            {
                mvwchgat(menuwin, i, 0, xmax, A_NORMAL, 1, NULL);
            }
            else
            {
                mvwchgat(menuwin, i, 0, xmax, A_STANDOUT, 0, NULL);
            }
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

    WINDOW *menuwin;
    WINDOW *win;
    Menu *menus;
    int num_menus;
    int selected;
};

#endif
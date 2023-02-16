#include <iostream>
#include <unordered_map>
#include <string>
#include <ncurses.h>

class Unit
{
public:
    virtual void Display(int x, int y) = 0;
};

class Soldier : public Unit
{
public:
    Soldier(char symbol) : symbol_(symbol) {}

    void Display(int x, int y) override
    {
        mvaddch(y, x, symbol_);
    }

private:
    char symbol_;
};

class UnitFactory
{
public:
    Unit *GetUnit(char symbol)
    {
        if (units_.find(symbol) == units_.end())
        {
            units_[symbol] = new Soldier(symbol);
        }
        return units_[symbol];
    }

private:
    std::unordered_map<char, Unit *> units_;
};

int main()
{
    initscr();
    noecho();
    curs_set(0);

    UnitFactory unit_factory;

    Unit *archer = unit_factory.GetUnit('A');
    int x = 1, y = 2;
    archer->Display(x, y);

    refresh();
    while (true)
    {
        int ch = getch();
        switch (ch)
        {
        case 'w':
            y--;
            break;
        case 's':
            y++;
            break;
        case 'a':
            x--;
            break;
        case 'd':
            x++;
            break;
        default:
            break;
        }
        clear();
        archer->Display(x, y);
        refresh();
    }

    endwin();

    return 0;
}

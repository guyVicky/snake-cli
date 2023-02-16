#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

int main()
{

    initscr();
    halfdelay(1);
    noecho();
    curs_set(0);
    int i = 4, j = 5;
    while (1)
    {

        mvprintw(i++, j, "%d    %d", x, y);
        if (i == LINES - 1)
        {
            i = 0;
            j = j + 20;
        }
        refresh();
        // getch();
    }

    endwin();

    return 0;
}
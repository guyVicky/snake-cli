#include "main.h"

typedef struct snk
{
    int positions[100][2];
    int head;
    int tail;
    char direction;
    char spr;
    char spr_head;
    int score;
} Snake;

typedef struct food
{
    int position[2];
    int value;
    char spr;
} Fruit;

// coordinates are stored in {x,y}
Snake s1 = {{{3, 5}, {4, 5}, {5, 5}, {5, 6}, {6, 6}, {7, 6}, {8, 6}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}}, 11, 0, 'r', '#', 'O', 0};

Fruit f1 = {{20, 10}, 1, '+'};

int collision_check()
{
    int de[2] = {s1.positions[s1.head][0], s1.positions[s1.head][1]};
    // wall check
    if (de[0] == 0 || de[0] == COLS - 1 || de[1] == 0 || de[1] == LINES - 1)
    {
        return TRUE;
    }
    // body check
    for (int i = 0; i < s1.head - 2; i++)
    {
        if (s1.positions[i][0] == de[0])
        {
            if (s1.positions[i][1] == de[1])
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int fruit_check()
{
    int de[2] = {s1.positions[s1.head][0], s1.positions[s1.head][1]};
    int fe[2] = {f1.position[0], f1.position[1]};
    if (de[0] == fe[0] && de[1] == fe[1])
    {
        return TRUE;
    }
    return FALSE;
}
void turn()
{
    int x = getch();
    if (s1.direction == 'u' || s1.direction == 'd')
    {
        s1.direction = (x == 'd') ? 'r' : (x == 'a') ? 'l'
                                                     : s1.direction;
    }
    else if (s1.direction == 'l' || s1.direction == 'r')
    {
        s1.direction = (x == 'w') ? 'u' : (x == 's') ? 'd'
                                                     : s1.direction;
    }
}

void spawn_fruit()
{
    mvaddch(f1.position[1], f1.position[0], ' ');

    int x = rand() % (COLS - 1) + 1;
    int y = rand() % (LINES - 1) + 1;
    mvaddch(y, x, f1.spr);

    f1.position[0] = x;
    f1.position[1] = y;
}

void update_loc()
{

    int de[2] = {s1.positions[0][0], s1.positions[0][1]};
    for (int i = s1.tail; i < s1.head; i++)
    {
        s1.positions[i][0] = s1.positions[i + 1][0];
        s1.positions[i][1] = s1.positions[i + 1][1];
    }
    // direction it will progress towards
    switch (s1.direction)
    {
    case 'r':
        s1.positions[s1.head][0]++;
        break;
    case 'u':
        s1.positions[s1.head][1]--;
        break;
    case 'l':
        s1.positions[s1.head][0]--;
        break;
    case 'd':
        s1.positions[s1.head][1]++;
        break;
    }

    for (int i = s1.tail; i < s1.head; i++)
    {
        mvaddch(s1.positions[i][1], s1.positions[i][0], s1.spr);
    }
    mvaddch(s1.positions[s1.head][1], s1.positions[s1.head][0], s1.spr_head);

    refresh();
    mvaddch(de[1], de[0], ' ');
}

void display_game_over(int x, int y)
{
    mvaddstr(y++, x, "   _________    __  _________   ____ _    ____________");
    mvaddstr(y++, x, "  / ____/   |  /  |/  / ____/  / __ \\ |  / / ____/ __ \\");
    mvaddstr(y++, x, " / / __/ /| | / /|_/ / __/    / / / / | / / __/ / /_/ /");
    mvaddstr(y++, x, "/ /_/ / ___ |/ /  / / /___   / /_/ /| |/ / /___/ _, _/");
    mvaddstr(y++, x, "\\____/_/  |_/_/  /_/_____/   \\____/ |___/_____/_/ |_|");
    mvprintw(y + 4, x + 23, "Score: %d", s1.score);
    refresh();
}

int main()
{
    srand(time(NULL));

    // setup_snake();
    initscr();
    halfdelay(2);
    noecho();
    curs_set(0);
    // titlescreen();
    border('#', '#', '#', '#', '#', '#', '#', '#');
    // for (int i = s1.tail; i <= s1.head; i++)
    // {
    //     mvaddch(s1.positions[i][1], s1.positions[i][0], '%');
    // }
    spawn_fruit();
    refresh();

    // game loop
    while (1)
    {
        if (collision_check())
        {
            break;
        }
        turn();
        if (fruit_check())
        {
            int newhead = s1.head + 1;
            switch (s1.direction)
            {
            case 'r':
                s1.positions[newhead][0] = s1.positions[s1.head][0]++;
                s1.positions[newhead][1] = s1.positions[s1.head][1];
                break;
            case 'u':
                s1.positions[newhead][0] = s1.positions[s1.head][0];
                s1.positions[newhead][1] = s1.positions[s1.head][1]--;
                break;
            case 'l':
                s1.positions[newhead][0] = s1.positions[s1.head][0]--;
                s1.positions[newhead][1] = s1.positions[s1.head][1];
                break;
            case 'd':
                s1.positions[newhead][0] = s1.positions[s1.head][0];
                s1.positions[newhead][1] = s1.positions[s1.head][1]++;
                break;
            }

            s1.score += 2;
            s1.head++;
            spawn_fruit();
        }
        update_loc();
        mvprintw(1, 1, " Score - %d", s1.score);
    }
    clear();
    border('#', '#', '#', '#', '#', '#', '#', '#');
    display_game_over(COLS / 2 - 26, LINES / 2 - 3);
    cbreak();
    napms(2000);
    mvprintw(LINES - 4, COLS / 2 - 16, "Press any button to continue...");
    getch();
    return 0;
}
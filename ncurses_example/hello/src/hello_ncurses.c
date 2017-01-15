#include <stdlib.h>
#include <stdio.h>
#include <curses.h>


#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;

const char *choices[] = { 
    "Hello, world!",
    "Choice #2",
    "Choice #3",
    "Choice #4",
    "Exit",
};

int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);

int main()
{
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */

    int mx,my;
    getmaxyx(stdscr, my, mx);
    // keypad( stdscr, TRUE);

    startx = (mx - WIDTH) / 2;
    starty = (my - HEIGHT) / 2;
        
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    
    mvprintw(0, 0, "Use arrow keys to go up and down, press enter to select a choice");
    mvhline( 1, 0, ACS_HLINE , mx);
    refresh();
    
    print_menu(menu_win, highlight);
    
    while(1)
    {
        c = wgetch(menu_win);
        switch(c)
        {
        case KEY_UP:
            if(highlight == 1)
                highlight = n_choices;
            else
                highlight--;
            mvprintw( 0, 0, "Choice %d with choice string %s\n", highlight, choices[highlight - 1]);
            refresh();
            break;
        case KEY_DOWN:
            if(highlight == n_choices)
                highlight = 1;
            else 
                highlight++;
            mvprintw( 0, 0, "Choice %d with choice string %s\n", highlight, choices[highlight - 1]);
            refresh();
            break;
        case KEY_LEFT:
        case KEY_RIGHT:
            break;
        case 10:
        case KEY_ENTER:
            choice = highlight;
            break;
        default:
            mvprintw(24, 0, "Character pressed is = %3d, hopefully it can be printed as '%c'", c, c);
            refresh();
            break;
        }
        
        print_menu(menu_win, highlight);
        if(choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    
    wclear( menu_win );
    wrefresh( menu_win );
    delwin( menu_win );
    refresh();
    mvprintw(24, 0, "You picked choice %d with choice string %s\n", choice, choices[choice - 1]);
    // clrtoeol();
    refresh();
    
    getch();
    endwin();
    
    return 0;
}


void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;    
    
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    
    for(i = 0; i < n_choices; i++)
    {
        if(highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_win, A_REVERSE); 
            mvwprintw(menu_win, y+i, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y+i, x, "%s", choices[i]);
    }
    wrefresh(menu_win);
}

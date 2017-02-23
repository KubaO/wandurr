// wandurr1.cpp - game of wandering around doing stuff written in c++/ncurses hurr durr
// copyright 2017 inhabited.systems
// This program is covered by the MIT License.
// See the file LICENSE included with this distribution for terms.

// see the file README.md for more information, including how to compile and
// run this program.

// wandurr1 does not use classes, so this code will look more C-like.  I may do
// a wandurr2 that uses classes.

#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int row = 0, col = 0, rows = 0, cols = 0, playery = 0, playerx = 0;
int halfy = 0, halfx = 0;
const int cpairs=7;

typedef struct {
    char    occupant;
    int     y;
    int     x;
    char    color;
} Cell;

            
vector<vector<Cell> > vec2d;

void vec2dinitrandint(vector<vector<Cell>>& pvec, int rsize);
void print2dvec(vector<vector<Cell>> pvec, string title);
void drawgamescreen();
void drawhelpscreen();
static void finish(int sig);

int main(void)
{
    //int row = 0, col = 0;

    int ch = 0;
    time_t timenow;
    timenow = time(NULL);
    srand(timenow);
    //const int rows = 15, cols = 40;

    // what the hell is this crap?  FIX IT!
    (void) signal(SIGINT, finish);

    (void) initscr();
    keypad(stdscr, TRUE);
    (void) nonl();
    (void) cbreak();
    (void) echo();

    addstr("Wandurr! Press any key to begin:\n");
    curs_set(0);
    getmaxyx(stdscr,rows,cols);
    halfy = rows/2;
    halfx = cols/2;
    playery = halfy;
    playerx = halfx;
    rows-=2;
    cols-=2;
    printw("rows: %d cols: %d", rows, cols);
    refresh();
    getch();

//    vector<vector<int> > vec2d;
    vec2d.resize(rows);
    for (int i = 0; i < rows; ++i)
        vec2d[i].resize(cols);
    vec2dinitrandint(vec2d, cpairs);
    //print2dvec(vec2d, "vec2d");

    if (has_colors())
    {
        //addstr("has_colors()\n");
        refresh();
        //getch();
        start_color();
        init_pair(0, COLOR_WHITE, COLOR_BLACK);
        init_pair(1, COLOR_WHITE, COLOR_RED);
        init_pair(2, COLOR_WHITE, COLOR_GREEN);
        init_pair(3, COLOR_WHITE, COLOR_YELLOW);
        init_pair(4, COLOR_WHITE, COLOR_BLUE);
        init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(6, COLOR_WHITE, COLOR_CYAN);
        init_pair(7, COLOR_WHITE, COLOR_WHITE);
        init_pair(8, COLOR_YELLOW, COLOR_GREEN);
        init_pair(9, COLOR_BLACK, COLOR_GREEN);
    }

    nodelay(stdscr, TRUE);
    move(rows+1,0);
    addstr("Press any key to quit.\n");
    getch();

    keypad(stdscr, TRUE);
    do
    {
        ch = getch();
        switch(ch)
        {
            case KEY_DOWN:
                //addstr("Down\n");
                playery++;
                break;
            case KEY_UP:
                //addstr("Up\n");
                playery--;
                break;
            case KEY_LEFT:
                //addstr("Left\n");
                playerx--;
                break;
            case KEY_RIGHT:
                //addstr("Right\n");
                playerx++;
                break;
            default:
                break;
        }
        drawgamescreen();
        refresh();
    } while(ch != '~');
                

    endwin();
    //finish(0);
    return 0;
}

void vec2dinitrandint(vector<vector<Cell>>& pvec, int rsize)
{
    for (unsigned int i = 0; i < pvec.size(); i++)
    {
        for (unsigned int j = 0; j < pvec[i].size(); j++)
        {
            // this is supposed to be green
            pvec[i][j].color = 2;
            if (rand()%100==1) pvec[i][j].occupant = '$';
            else pvec[i][j].occupant = ' ';
            // cout << "pvec[" << i << "][" << j << "] = " << pvec[i][j].color << "\n";
        }
    }
}

void print2dvec(vector<vector<Cell>> pvec, string title)
{
    // TODO: change this crap to use ncurses instead of cout!!! or just delete this?
    // print out the 2d vector of int passed in as pvec
    cout << "\n" << title << "\n";
    for (unsigned int i = 0; i < pvec.size(); i++)
    {
        for (unsigned int j = 0; j < pvec[i].size(); j++)
        {
            cout << pvec[i][j].color << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void drawgamescreen()
{
    int rowoffset = 1, coloffset = 1;

    for(row=2; row < rows; row++) {
        for(col=2; col < cols-3; col++) {
            move(row+rowoffset,col+coloffset);
            //attrset(COLOR_PAIR(rand()%7+1));
            attrset(COLOR_PAIR(vec2d[row][col].color));
            //if (vec2d[row][col].color > 0) vec2d[row][col].color=vec2d[row][col].color-1;
            //else vec2d[row][col].color =  rand()%cpairs;
            if(vec2d[row][col].occupant == '$')
                attrset(COLOR_PAIR(8));
            else
                attrset(COLOR_PAIR(2));

            addch(vec2d[row][col].occupant);
        }
        //napms(10);
    }
    attrset(COLOR_PAIR(9));
    move(playery,playerx);
    addch('X');
    refresh();
}

void drawhelpscreen()
{
}

static void finish(int sig)
{
    endwin();
    exit(0);
}

#include <ncurses.h>
#include <string>
#include <vector>

#include "Rubiks.h"

#define WHITE 11
#define GREEN 12
#define BLUE 13
#define RED 14
#define ORANGE 15
#define YELLOW 16
#define INPWIN 50
#define KEY_RETURN 10

// “I’m not exactly Zhuge Liang or Kuroda Kanbei. I don’t have any plans.”

using namespace std;

WINDOW *cubeSide[9];
WINDOW *inpWin;
int currSide = 2; // current cube side that is displayed
Rubiks cube; // our main character
int XCENTER, YCENTER;

const int KEY_ESCAPE = 27;

void bx(){
    // cube
    int y = (LINES/2) - 3;
    int x = (COLS/2) - 6;
    int clr = 11;
    for(int b=y;b<y+6;b+=2){
        for(int k=x; k<x+12; k+=4){
            attron(COLOR_PAIR(clr) | A_BOLD);
            for(int i=k;i<k+4;i++){
                for(int j=b;j<b+2;j++){
                    mvprintw(j, i, " ");
                }
            }
            attron(COLOR_PAIR(clr) | A_BOLD);
            clr++;
            if(clr > 16) clr = 11;
        }
    }
}

int color(char ch){
    switch(ch){
        case 'r':
            return RED;
        case 'w':
            return WHITE;
        case 'g':
            return GREEN;
        case 'y':
            return YELLOW;
        case 'o':
            return ORANGE;
        case 'b':
            return BLUE;
        default:
            return -1;
    }
}

void updateWinCube(string sideColors){
    // updates the window-cube
    for(int i=0; i<9; i++){
        wbkgd(cubeSide[i], COLOR_PAIR(color(sideColors[i])));
        wrefresh(cubeSide[i]);
    }
}

void initializeWinCube(void){
    // creating windows representing each block of a single side of RubiksCube
    int c_rows = 3, c_cols = c_rows*2; // size of one RubiksCube block
    int upward = (int)((LINES/100.00)*20);

    // to center the cube
    int y = (LINES/2) - (c_rows*3)/2 - upward;
    int x = (COLS/2) - (c_cols*3)/2;

    int block = 0, j = y;

    for(int row=0; row<3; row++){
        for(int i=x;i<x+(c_cols*3);i+=c_cols){
            cubeSide[block] = newwin(c_rows, c_cols, j, i);
            // box(cubeSide[block], ACS_VLINE, ACS_HLINE);
            // wrefresh(cubeSide[block]);
            block++;
        }
        j += c_rows;
    }
}

int rgb2Trgb(int rgb){
    if(rgb==0) return 0;
    // trgb stands for terminal specific rgb values that ranges from 0 to 1000
    int trgb;
    trgb = ((rgb*100)/255) * 10; // according to percentage, rgb%255=trgb%1000
    return trgb;
}

void parse_input(string input){
    cube.executeMoves(input);
    // updateWinCube(cube.getSideString(currSide));
}

bool isValidChar(char ch){
    char valids[] = "FfBbUuDdRrLlEeMmSsXxYyZz'2";
    for(int i=0;i<26;i++){
        if(valids[i] == ch) return true;
    }
    return false;
}

void updateSide(){
    char sides[] = {'U', 'L', 'F', 'B', 'R', 'D'};
    string side = "";
    char spaces[] = "         ";
    switch(currSide){
        case 0:
            side = "UP";
            break;
        case 1:
            side = "LEFT";
            break;
        case 2:
            side = "FRONT";
            break;
        case 3:
            side = "BACK";
            break;
        case 4:
            side = "RIGHT";
            break;
        case 5:
            side = "DOWN";
            break;
        default:
            side = "UNDEFINED";
    }
    int x = (COLS / 2) - 4;
    move(1, x);
    addstr(spaces);
    x = (COLS / 2) - (side.length() / 2);
    move(1, x);
    addstr(side.c_str());
    refresh();
}

int main(int argc, char ** argv)
{
    // init screen and sets up screen
    initscr();
    curs_set(FALSE); // for hiding the blinking cursor
    if(!has_colors()){
        printw("Your screen doesn't support colors, exiting...\n");
        endwin();
        return 0;
    } else{
        start_color();
    }

    if(!can_change_color()){
        init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
        init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
        init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
        init_pair(RED, COLOR_RED, COLOR_RED);
        init_pair(ORANGE, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(YELLOW, COLOR_MAGENTA, COLOR_MAGENTA);
    } else {
        // initializing colors 
        init_color(WHITE, 1000, 1000, 1000);
        init_color(GREEN, rgb2Trgb(39), rgb2Trgb(183), 0);
        init_color(BLUE, rgb2Trgb(2), rgb2Trgb(107), rgb2Trgb(206));
        init_color(RED, rgb2Trgb(239), rgb2Trgb(4), rgb2Trgb(8));
        init_color(ORANGE, rgb2Trgb(252), rgb2Trgb(83), rgb2Trgb(27));
        // init_color(YELLOW, 988, 780, 156);
        init_color(YELLOW, rgb2Trgb(238), rgb2Trgb(252), rgb2Trgb(50));

        // initializing color pairs
        init_pair(WHITE, WHITE, WHITE);
        init_pair(GREEN, GREEN, GREEN);
        init_pair(BLUE, BLUE, BLUE);
        init_pair(RED, RED, RED);
        init_pair(ORANGE, ORANGE, ORANGE);
        init_pair(YELLOW, YELLOW, YELLOW);
        init_pair(INPWIN, WHITE, GREEN);
    }
    keypad(stdscr, TRUE);
    raw();
    cbreak();
    noecho();

    refresh();
    initializeWinCube();
    updateSide();
    refresh();

    YCENTER = LINES / 2;
    XCENTER = COLS / 2;

    inpWin = newwin(LINES - (int)((LINES/100.00)*70), COLS, (int)((LINES/100.00)*70), 0);
    // box(inpWin, ACS_VLINE, ACS_HLINE);
    wbkgd(inpWin, COLOR_PAIR(INPWIN));
    wmove(inpWin, 1, 1);
    waddch(inpWin, '>');
    wrefresh(inpWin);


    int ch;
    int ext = 0;
    int side = 2;
    cube.inputFromFile("cube.txt");
    updateWinCube(cube.getSideString(currSide));
    string inp;
    while(ext != 1){
        // print to screen
        ch = getch();
        // beep();
        switch(ch){
            case KEY_UP:
                side++;
                if(side>5) side=0;
                break;

            case KEY_DOWN:
                side--;
                if(side<0) side=5;
                break;

            case KEY_LEFT:
                side--;
                if(side<0) side=5;
                break;

            case KEY_RIGHT:
                side++;
                if(side>5) side=0;
                break;

            case KEY_RETURN:{
                parse_input(inp);
                wmove(inpWin, 1, 1);
                wdeleteln(inpWin);
                wdeleteln(inpWin);
                wmove(inpWin, 2, 1);
                wprintw(inpWin, "Excuted Moves: %s", inp.c_str());
                wmove(inpWin, 1, 1);
                waddch(inpWin, '>');
                wrefresh(inpWin);
                inp.clear();
                break;
            }

            case KEY_BACKSPACE:
                if(inp.length() == 0) break;
                wmove(inpWin, 1, inp.length());
                wdelch(inpWin);
                wrefresh(inpWin);
                inp.pop_back();
                break;

            case KEY_ESCAPE:
                ext = 1;
                break;

            default:{
                if(isValidChar(ch)){
                    if(ch >= 97 && ch <= 122) ch = ch - 32;
                    inp.push_back(ch);
                    waddch(inpWin,ch);
                    // wprintw(inpWin,"%d", ch);
                    wrefresh(inpWin);
                }
            }
        }
        refresh();
        currSide = side;
        updateSide();
        updateWinCube(cube.getSideString(side));
        refresh();
    }


    // refreshes the screen
    // refresh();

    // pause the screen output
    // curs_set(TRUE);

    // getch();

    // deallocates memory and ends ncurses
    endwin();
    return 0;
}



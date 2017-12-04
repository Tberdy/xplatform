/* 
 * File:   XPlatform.c
 * Author: Tberdy
 *
 * Created on 30 septembre 2016, 00:09
 */

#include "XPlatform.h"

#ifdef WINDOWS

char xplt_getch() {
    return getch();
}

void xplt_clrscr() {
    system("cls");
}

void xplt_gotoligcol(int lig, int col) {
    COORD Coord;
    Coord.X = col;
    Coord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
}

void xplt_set_color(int text, int foreground) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, foreground * 16 + text);
}

#else

char xplt_getch() {
    char c = 0;
    system("/bin/stty raw");
    while (c == 0) {
        c = getchar();
    }
    system("/bin/stty cooked");
    return c;
}

void xplt_clrscr() {
    system("clear");
}

void xplt_gotoligcol(int lig, int col) {
    printf("\033[%d;%dH", lig + 1, col + 1);
}

void xplt_set_color(int text, int foreground) {
    char color[4];
    if (text >= 0 && text < 100 && foreground >= 0 && foreground < 100) {
        sprintf(color, "%d", text);
        printf("\033[%sm", color);
        sprintf(color, "%d", foreground + 10);
        printf("\033[%sm", color);
    }
}

#endif
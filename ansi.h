#include <stdio.h>
#include <stdlib.h>
/*
    some ansi functions
*/
#define BLACK   0
#define RED     1
#define GREEN   2
#define YELLOW  3
#define BLUE    4
#define MAGNETA 5
#define CYAN    6
#define WHITE   7
#define ANSI_GOTOXY(z,s)    printf("\033[%d;%dH", (z), (s))
#define ANSI_CLEAR_SCREEN() printf("\033[2J")
#define ANSI_DEFAULT()      printf("\033[0m")
#define ANSI_COLOR(f,b)     printf("\033[%d;%dm", (f) + 30, (b) + 40)
#define ANSI_FG_LCOLOR(f)   printf("\033[0;%dm", (f) + 30)
#define ANSI_FG_HCOLOR(f)   printf("\033[1;%dm", (f) + 30)


//static int screenwidth, screenheight;



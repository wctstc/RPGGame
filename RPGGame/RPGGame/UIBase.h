


#include <windows.h>
#include <stdio.h>



void gotoxy(int x,int y);
void print( char c );
void print( int x, int y, char c );
void print( int x, int y, char *buffer );
void clearxy( int x, int y );
void clearxy( int x1, int x2, int y1, int y2 );
void clear( );
void readxy( int x, int y, char &character );
void setcolor(int fg,int bg);

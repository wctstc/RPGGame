#include "UIBase.h"

#include <stdio.h>

void gotoxy(int x,int y)
{
	COORD c;

	c.X=x;c.Y=y;
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE),c);

}

void print( char c )
{
	printf( "%c",c );
}
void print( int x, int y, char c )
{
	gotoxy( x, y );
	print( c );
}
void print( int x, int y, char *buffer )
{
	gotoxy( x, y );
	
//	for( int i = 0; buffer[i] != '\0'; i++ )
//		printf( "%c", buffer[i] );
	printf( "%s", buffer );
}
void clearxy( int x, int y )
{
	gotoxy( x, y );
	printf( " " );
}

void clearxy( int x1, int x2, int y1, int y2 )
{
	if( ( x2 - x1 ) < 0 || ( y2 - y1 ) < 0 )
		return;

	for( int i = 0 ; i < y2 - y1 + 1; i++ )
	{
		gotoxy( x1, y1 + i );
		for( int j = 0; j < x2 - x1 + 1; j++ )
		{
			printf( " " );
		}
	}
}


void clear( )
{
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;                            
	HANDLE    hConsoleOut;
	COORD    Home = {0,0};
	DWORD    dummy;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
	FillConsoleOutputCharacter( GetStdHandle( STD_OUTPUT_HANDLE),' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
}
void readxy( int x, int y, char &character )
{

	DWORD read;
	COORD coord = {x, y};
	ReadConsoleOutputCharacter( GetStdHandle( STD_OUTPUT_HANDLE ), &character, 1, coord, &read );
}

void setcolor(int fg,int bg)
{
	WORD wc;
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	bg<<=4;
	wc=(fg & 0x000f )|(bg & 0x00f0);

	SetConsoleTextAttribute(h,wc);
}



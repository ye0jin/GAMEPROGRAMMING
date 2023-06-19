#include "Console.h"
#include <conio.h>


void FullScreen()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL);
}

void Gotoxy(int x, int y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cur = { x,y };
	SetConsoleCursorPosition(hout, Cur);
}

bool Gotoxytest(int, int)
{
	return false;
}

void GotoxyPlayer(int x, int y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cur = { x * 2,y };
	SetConsoleCursorPosition(hout, Cur);
}

void CursorSet(bool _bYis, DWORD _dwSize)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.bVisible = _bYis;
	info.dwSize = _dwSize;
	SetConsoleCursorInfo(hout, &info);
}

void SetColor(int color, int bgcolor)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout, (bgcolor << 4) | color);
}

int GetColor()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hout, &info);
	int color = info.wAttributes & 0xf;

	return color;
}

int GetbgColor()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hout, &info);
	int color = info.wAttributes & 0xf >> 4;

	return color;
}

void fontsize(UINT _weight, UINT _sizex, UINT _sizey)
{
	static CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hout, false, &font);
	font.FontWeight = _weight;
	font.dwFontSize.X = _sizex;
	font.dwFontSize.Y = _sizey;
	SetCurrentConsoleFontEx(hout, false, &font);
}

#pragma once

#include <windows.h>

enum class COLOR
{
	BLACK, BLUE, GREEN, SKYBLUE, RED,
	VOILET, YELLO, LIGHT_GRAY, GRAY, LIGHT_BLUE,
	LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
	LIGHT_YELLO, WHITE
};


void FullScreen();
void Gotoxy(int, int);
bool Gotoxytest(int, int);
void GotoxyPlayer(int, int);
void CursorSet(bool, DWORD);
void SetColor(int, int);
int GetColor();
int GetbgColor();
void fontsize(UINT _weight, UINT _sizex, UINT _sizey);
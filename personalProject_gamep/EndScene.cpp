#include "EndScene.h"
#include "GameLogic.h"
#include "Console.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>

using namespace std;

bool isBlink = true;
int GameOverDraw(int currentScore, int maxScore)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) return 1;
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
	
	Gotoxy(0, 1);
	wcout << L"		  	        .∧＿∧　　　　∧＿∧" << endl;
	wcout << L"			        (*･ω･ヾ⌒∨⌒ヽ･ω･*)" << endl;
	wcout << L"			        ( > ( Score: " << currentScore << " ) <  )" << endl;
	wcout << L"			        (＿＿⊃＼_ _／⊂＿＿ )" << endl << endl;

	
	wcout << L"			          Highest Score: " << maxScore << endl << endl;

	if(isBlink) wcout << L"			     Tap Space to Restart. . ." << endl;
	isBlink = !isBlink;

	int Curmode = _setmode(_fileno(stdout), prevmode);

	return 0;
}
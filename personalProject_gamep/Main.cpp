#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "StartScene.h"
#include "EndScene.h"
#include "GameLogic.h"
#include "Console.h"

using namespace std;
int maxScore = 0;

int main()
{
	// 커서 숨기기
	CursorSet(false, 1);
	system("mode con:cols=88 lines=20");

	// 타이틀 화면
	while (true)
	{
		Sleep(100);
		GameTitle();
		int iMenu = MenuDraw();

		if (iMenu == 0)
		{
			system("cls");
			break;
		}
		else if (iMenu == 1)
		{
			InfoDraw();
			system("cls");
			continue;
		}
		else if (iMenu == 2)
		{
			system("cls");
			cout << endl << "게임을 종료합니다." << endl;
			for (int i = 0; i < 3; i++)
			{
				cout << "\r" << 3 - i << ". . .";
				Sleep(1000);
			}

			system("cls");
			cout << endl << "게임이 종료되었습니다." << endl;
			return 0;
		}

		Sleep(100);
	}
	while (true)
	{
		Sleep(100);
		int score = 0;
		int waitFrame = 0;
		while (true)
		{
			if (GameOver())
			{
				score = ReturnScore();
				if (score > maxScore) maxScore = score;
				break; // 게임 오버
			}
			Update();
			if (TryHeal(true) && waitFrame < 2)
			{
				waitFrame++;
			}
			else
			{
				TryHeal(false);
				waitFrame = 0;
			}
		}

		Reset();
		Sleep(200);
		system("cls");

		while (true)
		{
			Gotoxy(0, 1);
			int x = GameOverDraw(score, maxScore);
			if (x != 0) break;
		}

		Sleep(100);
		system("cls");
	}
	
	return 0;
}
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "StartScene.h"
#include "EndScene.h"
#include "GameLogic.h"
#include "Console.h"

using namespace std;
int maxScore = 0;

int main()
{
	// Ŀ�� �����
	CursorSet(false, 1);
	system("mode con:cols=88 lines=20");

	// Ÿ��Ʋ ȭ��
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
			cout << endl << "������ �����մϴ�." << endl;
			for (int i = 0; i < 3; i++)
			{
				PlaySound(L"blipSelect.wav", 0, SND_FILENAME | SND_ASYNC);

				cout << "\r" << 3 - i << ". . .";
				Sleep(1000);
			}

			PlaySound(L"magic_03.wav", 0, SND_FILENAME | SND_ASYNC);
			system("cls");
			cout << endl << "������ ����Ǿ����ϴ�." << endl;

			Sleep(1000);

			return 0;
		}

		Sleep(100);
	}

	Sleep(300);
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
				break; // ���� ����
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
		PlaySound(L"magic_03.wav", 0, SND_FILENAME | SND_ASYNC);

		while (true)
		{
			Gotoxy(0, 1);
			int x = GameOverDraw(score, maxScore);
			if (x != 0)
			{
				PlaySound(L"click.wav", 0, SND_FILENAME | SND_ASYNC);
				break;
			}
		}

		Sleep(100);
		system("cls");
	}
	
	return 0;
}
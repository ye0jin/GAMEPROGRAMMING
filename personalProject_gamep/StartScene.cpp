#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include "StartScene.h"
#include "Console.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

void GameTitle()
{
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L"				*｡*.。*∧,,,∧" << endl;
	wcout << L"				ヾ(⌒(_ = •ω•)_♥" << endl << endl;

	wcout << L"██████╗ ██╗   ██╗███╗   ██╗███╗   ██╗██╗███╗   ██╗ ██████╗      ██████╗ █████╗ ████████╗" << endl;
	wcout << L"██╔══██╗██║   ██║████╗  ██║████╗  ██║██║████╗  ██║██╔════╝     ██╔════╝██╔══██╗╚══██╔══╝" << endl;
	wcout << L"██████╔╝██║   ██║██╔██╗ ██║██╔██╗ ██║██║██╔██╗ ██║██║  ███╗    ██║     ███████║   ██║" << endl;
	wcout << L"██╔══██╗██║   ██║██║╚██╗██║██║╚██╗██║██║██║╚██╗██║██║   ██║    ██║     ██╔══██║   ██║" << endl;
	wcout << L"██║  ██║╚██████╔╝██║ ╚████║██║ ╚████║██║██║ ╚████║╚██████╔╝    ╚██████╗██║  ██║   ██║" << endl;
	wcout << L"╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═══╝ ╚═════╝      ╚═════╝╚═╝  ╚═╝   ╚═╝" << endl;

	int Curmode = _setmode(_fileno(stdout), prevmode);
}


int KeyController()
{
	while (true)
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();

			switch (input)
			{
			case 72:
				return (int)Key::UP;
			case 80:
				return (int)Key::DOWN;
			default:
				break;
			}
		}
		else if (input == 32)
		{
			return (int)Key::SPACE;
		}
	}
	return 0;
}

int MenuDraw()
{
	int x = 35;
	int y = 12;

	Gotoxy(x, y);
	wcout << L"GAME START" << endl;
	Gotoxy(x, y + 1);
	wcout << L"HOW TO PLAY" << endl;
	Gotoxy(x, y + 2);
	wcout << L"EXIT" << endl;

	while (true)
	{
		int iKey = KeyController();
		PlaySound(L"click.wav", 0, SND_FILENAME | SND_ASYNC);

		switch (iKey)
		{
		case (int)Key::UP:
		{
			if (y > 12)
			{
				Gotoxy(x - 2, y);
				wcout << L" ";
				Gotoxy(x - 2, --y);
				wcout << L">";
			}
		}
		break;
		case (int)Key::DOWN:
		{
			if (y < 14)
			{
				Gotoxy(x - 2, y);
				wcout << L" ";
				Gotoxy(x - 2, ++y);
				wcout << L">";
			}
		}
		break;
		case (int)Key::SPACE:
		{
			return y - 12;
		}
		break;
		default:
			break;
		}
	}

	return 0;
}

void InfoDraw()
{
	system("cls");
	cout << endl << endl;
	cout << "[게임 방법]" << endl;
	cout << "- 스페이스바로 점프하여 다가오는 장애물들을 피하세요!" << endl;
	cout << "- 좌측 쉬프트키로 코인 3개를 사용해 50% 확률로 체력을 회복할 수 있습니다. \n코인은 개당 10점의 점수를 가지고 있습니다.\n" << endl << endl;

	cout << "계속하시려면 아무 키나 누르세요 . . .";

	char a = _getch();
	PlaySound(L"click.wav", 0, SND_FILENAME | SND_ASYNC);

}

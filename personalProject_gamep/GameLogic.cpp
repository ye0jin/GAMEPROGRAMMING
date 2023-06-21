#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "GameLogic.h"
#include "Console.h"

using namespace std;

// 플레이어
bool foot;
bool isJump = false;
bool isMaxJump = false;

bool isGameOver = false;

// 장애물 
bool isObstacle = true;

int playerPos = 10; // 현재 포지션
int treePos = 0;

int mapPos = 14; // 맵 포지션 (고정값)
int introducePos = 15; // 설명 포지션 (고정값)
int maxJump = 6; // 점프 포지션 (고정값)

int coinPos = 0;
int coin = 0;
bool isCoin = true;

int score = 0; 
int life[5] = { 1,1,1,1,1 };
int currentLife = 4;

bool tryHealing = false;
bool healTF = false;

float speed = 4;

void Update()
{
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);

	if (currentLife < 0) // 라이프가 0보다 낮을 때
	{
		isGameOver = true;
		score += coin * 10; // 코인까지 점수 합산
		int Curmode = _setmode(_fileno(stdout), prevmode);

		return;
	}

	if (score >= 100) // 100점 넘어갈 때마다 스피드 증가
	{
		speed += 0.01;
	}

	if (!isObstacle) // 장애물이 있을 경우에만 체크
	{
		if ((playerPos >= 8 && playerPos <= 11) && (treePos >= 0 && treePos <= 10))
		{
			--life[currentLife];
			--currentLife;
			isObstacle = true;
		}
	}

	if (!isCoin) // 코인이 있을 경우에만 체크
	{
		if (coinPos <= 13 && playerPos == 10)
		{
			coin++;
			isCoin = true;
		}
	}
	

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) isJump = true; // 스페이스 누르거나 슬라이드 안 하고 있을 때 점프 활성화
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000 && currentLife < 4 && coin >= 3 && !tryHealing) // 피 회복
	{
		tryHealing = true;
		coin -= 3;
		srand(time(NULL));
		bool a = (rand() % 100) % 2 == 0;
		healTF = a;
		if (a)
		{
			++currentLife;
			life[currentLife] = 1;
		}
	}

	if(isJump) // 점프 중일 경우
	{
		JumpingCat();
	}

	Gotoxy(0, playerPos);
	DrawingCat();

	Gotoxy(0, mapPos);
	DrawingMap();

	score++;
	Gotoxy(0, 0);
	wcout <<L"Score: " << score << endl;
	wcout << L"Coin: " << coin << endl;
	wcout << L"Life: ";
	for (int i = 0; i < 5; i++)
	{
		if (life[i] == 1) wcout<< L"♥";
		else wcout << L"♡";
	}
	int Curmode = _setmode(_fileno(stdout), prevmode);
	
	Gotoxy(0, 17);
	cout << "스페이스바: 점프, 쉬프트키: 코인 세 개 사용하여 50% 확률로 피 회복";
	Sleep(100);
	system("cls");
}

void DrawingCat()
{	
	wcout << L"     ∧_∧" << endl;
	if(isJump)
		wcout << L"     (>‿<)" << endl;
	else
		wcout << L"     (•‿•)" << endl;
	wcout << L"     (U　U" << endl;

	if (foot)
	{
		wcout << L"    ｜  _つ" << endl;
		wcout << L"   `し´";
	}
	else
	{
		wcout << L"   ｜つ  _" << endl;
		wcout << L"      `し´";
	}

	foot = !foot;
}

void JumpingCat()
{
	if (playerPos > maxJump && !isMaxJump) // 플레이어 포지션이 아직 도달하지 않았을 경우 계속 위로 올라가기
	{
		--playerPos;
	}
	else if (playerPos == 10 && isMaxJump) // 땅에 발이 닿았고, 이미 한 번 점프를 했을 경우
	{
		// 초기화
		isJump = false;
		isMaxJump = false;
	}
	else if (isMaxJump) // 점프 최대치 도달 후
	{
		++playerPos;
	}
	else if (playerPos == maxJump) // 점프 최대치 도달 확인
	{
		isMaxJump = true;
	}
}

void DrawingMap()
{
	wcout << L"\n";
	wcout << L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
	if (ObstacleTF())
	{
		MakeTree();
	}

	if (MakeCoin())
	{
		MovingCoin();
	}
}

bool ObstacleTF()
{
	srand(time(NULL));
	if (isObstacle && coinPos<=50 && (rand() % 100) % 2 == 0)
	{
		treePos = 80;
		isObstacle = false;
		return true;
	}
	else if (!isObstacle)
	{
		return true;
	}

	return false;
}

void MakeTree()
{
	if (treePos > 0) // 아직 도달하지 않았을 경우
	{
		treePos -= speed;
	}
	else if (treePos <= 2)
	{
		isObstacle = true;
	}

	Gotoxy(treePos, 12);
	wcout << L"  ■■\n";
	Gotoxy(treePos, 13);
	wcout << L"  ■\n";
	Gotoxy(treePos, 14);
	wcout << L"  ■\n";

	treePos = clamp(treePos, 0, 80);
}

bool MakeCoin()
{
	srand(time(NULL));
	if (isCoin && treePos <= 60 && rand() % 50 < 10)
	{
		coinPos = 80;
		isCoin = false;
		return true;
	}
	else if (!isCoin)
	{
		return true;
	}

	return false;
}

void MovingCoin()
{
	if (coinPos > 0)
	{
		coinPos -= speed;
	}
	else if (coinPos <= 2)
	{
		isCoin = true;
	}

	Gotoxy(coinPos, 13);
	wcout << L"ⓒ";
	coinPos = clamp(coinPos, 0, 80);
}


int ReturnScore()
{
	return score;
}

bool GameOver()
{
	return isGameOver;
}

bool TryHeal(bool tryH)
{
	if (tryHealing)
	{
		Gotoxy(40, 2);
		healTF ? wcout << "SUCCESS! ! !" : wcout << "FAIL. . .";
		if (!tryH) tryHealing = false;
		return tryHealing;
	}
	
	return tryHealing;
}

void Reset()
{
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
	int Curmode = _setmode(_fileno(stdout), prevmode);

	isJump = false;
	isMaxJump = false;

	isGameOver = false;

	// 장애물 
	isObstacle = true;

	playerPos = 10; // 현재 포지션
	treePos = 0;

	mapPos = 14; // 맵 포지션 (고정값)
	introducePos = 15; // 설명 포지션 (고정값)
	maxJump = 6;

	coinPos = 0;
	coin = 0;
	isCoin = true;

	score = 0;
	for (int i = 0; i < 5; i++)
	{
		life[i] = 1;
	}
	currentLife = 4;

	tryHealing = false;
	healTF = false;
}

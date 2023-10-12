#pragma once
#include "Quick functions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include "Enemy.h"
#include "Enums.h"
#include "UI.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ENTER 13
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77

void Clear()
{
	system("cls");
}
void Pause()
{
	system("Pause>0");
}
void Sleep(int miliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	while (_kbhit())
	{
		_getch();
	}
}


int DamageAdjustment(int setDamage)
{
	 return static_cast<int>(setDamage * RandomFloatNumber(0.8, 1.2) + 0.5);
}
double RandomFloatNumber(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(min, max);  

	return distrib(gen);
}
int RandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

MenuOptions ButtonPress()
{
    int button = 0;
    while (true)
    {
        button = _getch();
        if (button == 0 || button == 224)
        {
            switch (_getch())
            {
            case KEY_ARROW_UP:
            {
                return MenuOptions::MenuListUp;
                break;
            }
            case KEY_ARROW_DOWN:
            {
                return MenuOptions::MenuListDown;
                break;
            }
            case KEY_ARROW_LEFT:
            {
                return MenuOptions::MenuListLeft;
                break;
            }
            case KEY_ARROW_RIGHT:
            {
                return MenuOptions::MenuListRight;
                break;
            }
            }
        }
        else
        {
            if (button == KEY_W)
            {
                return MenuOptions::MenuListUp;
            }
            else if (button == KEY_S)
            {
                return MenuOptions::MenuListDown;
            }
            else if (button == KEY_A)
            {
                return MenuOptions::MenuListLeft;
            }
            else if (button == KEY_D)
            {
                return MenuOptions::MenuListRight;
            }
            else if (button == KEY_ENTER)
            {
                return MenuOptions::MenuListOption;
            }
        }
    }
}

bool YesOrNo()
{
    int playerChoiseInMenu = 0;
    std::string awnsers[2] = { "Yes", "No" };
    ui::MenuControll(awnsers, 2, playerChoiseInMenu);
    ui::ClearMenu();
    switch (playerChoiseInMenu)
    {
    case 0:
    {
        return true;
        break;
    }
    case 1:
    {
        return false;
        break;
    }
    default:
        return false;
        break;

    }
}
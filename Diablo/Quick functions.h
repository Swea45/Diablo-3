#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Enums.h"
#include "Enemy.h"

void Clear();
void Pause();
void Sleep(int miliseconds = static_cast<int>(ExtraInts::SleepStandardTime));
int RandomNumber(int min, int max);
double RandomFloatNumber(double min, double max);
int DamageAdjustment(int setDamage);
MenuOptions ButtonPress();
bool YesOrNo();
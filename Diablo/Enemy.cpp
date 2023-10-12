#include "Enemy.h"
#include "Enums.h"
#include "Quick functions.h"
#include "UI.h"

Enemy::Enemy()
{
	myHp;
	myStrength;
	myDexterety;
	myDodge;
	myIsAlive = true;


}

int Enemy::GetNormalAttack(int aOpponentsArmor)
{
	int damage = DamageAdjustment(myStrength);
	ui::PrintInMenu("The enemy deals: " + std::to_string(damage) + " damage!");
	ui::SetCursorPosition(static_cast<int>(MenuOptions::MenyStartX), static_cast<int>(MenuOptions::MenyStartY) + 1);
	Sleep(750);
	ui::Print("You block " + std::to_string(aOpponentsArmor) + " damage!");
	Sleep();
	return damage; 
}

bool Enemy::UppdateHp(int aChange)
{

	myHp -= aChange;
	if (myHp <= 0 && myIsAlive == true)
	{
		myIsAlive = false;
		return true;
	}
	else
	{
		return false;
	}
}

const int Enemy::GetHp() const
{
	return myHp;
}

const int Enemy::GetStrength() const
{
	return myStrength;
}

const int Enemy::GetDexterety() const
{
	return myDexterety;
}

const int Enemy::GetDodge() const
{
	return myDodge;
}


const bool Enemy::GetIsAlive() const
{
	return myIsAlive;
}

void Enemy::SetHp(int aNumber)
{
	myHp = aNumber;
}

void Enemy::SetStrength(int aNumber)
{
	myStrength = aNumber;
}

void Enemy::SetDexterety(int aNumber)
{
	myDexterety = aNumber;
}

void Enemy::SetDodge(int aNumber)
{
	myDodge = aNumber;
}

const int Enemy::GetSpriteSizeX() const
{
	return mySpriteSizeX;
}

void Enemy::ShowTarget(int aStartX, int aStartY, bool aTarget)
{
	if (aTarget == true)
	{
		ui::SetColor(ColorInt::RedColorText);
		ui::SetCursorPosition(aStartX, aStartY + mySpriteSizeY);
		for (int j = 0; j < mySpriteSizeX; j++)
		{
			if (j == 0 || j == mySpriteSizeX - 1)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << "=";
			}
		}
		ui::SetColor(ColorInt::WhiteColorText);
	}
	else
	{
		ui::SetCursorPosition(aStartX, aStartY + mySpriteSizeY);
		for (int j = 0; j < mySpriteSizeX; j++)
		{
			std::cout << " ";
		}
	}
}

void Enemy::PrintEnemySprite(int aStartX, int aStartY)
{
	ui::SetCursorPosition(aStartX, aStartY);
	std::cout << "  @#@@@@##(@@@  ";    
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << "@@             @";     
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << "@@   @@   @@   @";     
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << "@@             @";     
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << "@@             @";     
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << "%%#@#&@  #@(&*, ";     
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << "  (@&#     %@&%/";
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << "   @&&&  (&&@&& ";
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << "   @%&@@@@@(@,  ";     
	ui::SetCursorPosition(aStartX, ++aStartY);
	std::cout << " .@%@/     @(&@ ";         

	ui::SetCursorPosition(aStartX + mySpriteSizeX / 4, aStartY += 2);
	std::cout << "Hp: " << myHp << std::endl;
}
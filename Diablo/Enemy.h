#pragma once

class Enemy
{
public:
	Enemy();
	void ShowTarget(int aStartX, int aStartY, bool aTarget);
	void PrintEnemySprite(int aStartX, int aStartY);
	const int GetSpriteSizeX() const;
	bool UppdateHp(int aChange);
	const bool GetIsAlive() const;

	const int GetHp() const;
	const int GetStrength() const;
	const int GetDexterety() const;
	const int GetDodge() const;
	int GetNormalAttack(int aOpponentsArmor = 0);
	



	void SetHp(int aNumber);
	void SetStrength(int aNumber);
	void SetDexterety(int aNumber);
	void SetDodge(int aNumber);

private:
	int myHp;
	int myStrength;
	int myDexterety;
	int myDodge;
	bool myIsAlive;

	const int mySpriteSizeX = 16;
	const int mySpriteSizeY = 13;
};


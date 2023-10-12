#include "Items.h"
#include "Quick functions.h"
#include "Enums.h"
#include <string>
#include <vector>

Items::Items()
{
	myItemType;
	myLevel;
}


PrimeStats Items::GetPrimeStat()
{
	return myPrimeStat;
}

SecondaryStats Items::GetSecondaryStat()
{
	return mySecondaryStat;
}

int Items::GetPrimeStatBuff()
{
	return myPrimeStatBuff;
}

int Items::GetSecondaryStatBuff() 
{
	return mySecondaryStatBuff;
}

int Items::GetWeight()
{
	return myWeight;
}

int Items::GetLevel()
{
	return myLevel;
}

ItemType Items::GetItemType()
{
	return myItemType;
}

ItemSlot Items::GetItemSlot()
{
	return myItemSlot;
}

void Items::SetItemType(ItemType aItemType)
{
	myItemType = aItemType;
}

void Items::SetWeight(int aNumber)
{
	myWeight = aNumber;
}

void Items::SetItemSlot(ItemSlot aSlot)
{
	myItemSlot = aSlot;
}

void Items::SetPrimeStat(PrimeStats aPrimeStat)
{
	myPrimeStat = aPrimeStat;
}

void Items::SetSecondaryStat(SecondaryStats aSecondaryStat)
{
	mySecondaryStat = aSecondaryStat;
}

void Items::SetLevel(int aNumber)
{
	myLevel = aNumber;
}

void Items::SetPrimeStatBuff(int aNumber)
{
	myPrimeStatBuff = aNumber;
}

void Items::SetSecondaryStatBuff(int aNumber)
{
	mySecondaryStatBuff = aNumber;
}



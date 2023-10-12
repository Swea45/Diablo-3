#pragma once
#include <string>
#include "Enums.h"

class Items
{
	private:

		ItemType myItemType;
		ItemSlot myItemSlot;
		PrimeStats myPrimeStat;
		SecondaryStats mySecondaryStat;
		int myPrimeStatBuff;
		int mySecondaryStatBuff;
		int myLevel;
		int myWeight;

	public:
		Items();
		ItemType GetItemType();
		PrimeStats GetPrimeStat();
		SecondaryStats GetSecondaryStat();
		int GetPrimeStatBuff();
		int GetSecondaryStatBuff();
		int GetWeight();
		int GetLevel();
		ItemSlot GetItemSlot();
		

		void SetItemType(ItemType aItemType);
		void SetWeight(int aNumber);
		void SetItemSlot(ItemSlot aSlot);
		void SetPrimeStat(PrimeStats aPrimeStat);
		void SetSecondaryStat(SecondaryStats aSecondaryStat);
		void SetLevel(int aNumber);
		void SetPrimeStatBuff(int aNumber);
		void SetSecondaryStatBuff(int aNumber);
};


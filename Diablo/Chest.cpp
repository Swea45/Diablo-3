#include "Chest.h"
#include "Quick functions.h"
#include "Enums.h"
#include "Items.h"
#include "ItemFactory.h"
#include <vector>
#include <memory>

Chest::Chest()
{
	myInventory;
}

void Chest::Init(ItemFactory& aItemFactory)
{
	if (RandomNumber(static_cast<int>(ChestBase::Lock), static_cast<int>(ChestBase::LockChans)) == static_cast<int>(ChestBase::Lock))
	{
		myLockt = false;
	}
	else
	{
		myLockt = true;
		myLockDifficultyStr = RandomNumber(static_cast<int>(ChestBase::MinLockDifficulty), static_cast<int>(ChestBase::MaxLockDifficulty));
		myLockDifficultyDex = RandomNumber(static_cast<int>(ChestBase::MinLockDifficulty), static_cast<int>(ChestBase::MaxLockDifficulty));
	}

	CreateItems(RandomNumber(static_cast<int>(ChestBase::MinAmountOfItems), static_cast<int>(ChestBase::MaxAmountOfItems)), aItemFactory);
}

void Chest::CreateItems(int aAmount, ItemFactory& aItemFactory)
{
	std::vector<ItemType> randomItemType =
	{
		ItemType::Dagger,
		ItemType::Sword,
		ItemType::GreatSword,
		ItemType::Helm,
		ItemType::Armor,
	};

	for (int i = 0; i < aAmount; i++)
	{
		myInventory.push_back(aItemFactory.CreateItemWithRandomStats(randomItemType[RandomNumber(0, static_cast<int>(randomItemType.size()) - 1)]));
	}
		
}

int Chest::GetLockDifficultyStr()
{
	return myLockDifficultyStr;
}
int Chest::GetLockDifficultyDex()
{
	return myLockDifficultyDex;
}
bool Chest::GetLockt()
{
	return myLockt;
}
void Chest::SetLockt(bool aChestLockt)
{
	myLockt = aChestLockt;
}

int Chest::GetInventorySize()
{
	return static_cast<int>(myInventory.size());
}

std::vector<std::shared_ptr<Items>> Chest::GetInventory()
{
	return myInventory;
}

void Chest::RemoveItem(int aListNumber)
{
	myInventory.erase(myInventory.begin() + aListNumber);
}
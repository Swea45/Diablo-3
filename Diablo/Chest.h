#pragma once
#include <vector>
#include <memory>

class ItemFactory;
class Items;

class Chest
{
public:
	Chest();
	std::vector<std::shared_ptr<Items>> GetInventory();
	int GetLockDifficultyStr();
	int GetLockDifficultyDex();
	int GetInventorySize();
	bool GetLockt();
	void SetLockt(bool aDoorLockt);
	void RemoveItem(int aListNumber);
	void Init(ItemFactory& aItemFactory);

private:
	void CreateItems(int aAmount, ItemFactory& aItemFactory);
	std::vector<std::shared_ptr<Items>>  myInventory;
	int myLockDifficultyStr;
	int myLockDifficultyDex;
	bool myLockt;

};


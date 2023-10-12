#pragma once
#include <memory>
#include <array>
#include "Enums.h"
#include "Items.h"

class ItemFactory
{
private:
	std::array<Items, static_cast<int>(ItemType::count)> myItemTypes;
	int RandomLevel() const;

public:
	ItemFactory() = default;
	~ItemFactory() = default;

	void Init();

	std::shared_ptr<Items> CreateItem(const ItemType aItemType) const;
	std::shared_ptr<Items> CreateItemWithRandomStats(const ItemType aItemType) const;
};


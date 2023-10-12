#include "ItemFactory.h"
#include "Quick functions.h"

void ItemFactory::Init()
{
	myItemTypes[static_cast<int>(ItemType::Dagger)].SetItemType(ItemType::Dagger);
	myItemTypes[static_cast<int>(ItemType::Dagger)].SetItemSlot(ItemSlot::Weapon);
	myItemTypes[static_cast<int>(ItemType::Dagger)].SetWeight(3);
	myItemTypes[static_cast<int>(ItemType::Dagger)].SetLevel(1);
	myItemTypes[static_cast<int>(ItemType::Dagger)].SetPrimeStat(PrimeStats::Strength);
	myItemTypes[static_cast<int>(ItemType::Dagger)].SetSecondaryStat(SecondaryStats::Strength);
	myItemTypes[static_cast<int>(ItemType::Dagger)].SetPrimeStatBuff(1);
	myItemTypes[static_cast<int>(ItemType::Dagger)].SetSecondaryStatBuff(1);

	myItemTypes[static_cast<int>(ItemType::Sword)].SetItemType(ItemType::Sword);
	myItemTypes[static_cast<int>(ItemType::Sword)].SetItemSlot(ItemSlot::Weapon);
	myItemTypes[static_cast<int>(ItemType::Sword)].SetWeight(5);
	myItemTypes[static_cast<int>(ItemType::Sword)].SetLevel(1);
	myItemTypes[static_cast<int>(ItemType::Sword)].SetPrimeStat(PrimeStats::Strength);
	myItemTypes[static_cast<int>(ItemType::Sword)].SetSecondaryStat(SecondaryStats::Strength);
	myItemTypes[static_cast<int>(ItemType::Sword)].SetPrimeStatBuff(1);
	myItemTypes[static_cast<int>(ItemType::Sword)].SetSecondaryStatBuff(1);

	myItemTypes[static_cast<int>(ItemType::GreatSword)].SetItemType(ItemType::GreatSword);
	myItemTypes[static_cast<int>(ItemType::GreatSword)].SetItemSlot(ItemSlot::Weapon);
	myItemTypes[static_cast<int>(ItemType::GreatSword)].SetWeight(7);
	myItemTypes[static_cast<int>(ItemType::GreatSword)].SetLevel(1);
	myItemTypes[static_cast<int>(ItemType::GreatSword)].SetPrimeStat(PrimeStats::Strength);
	myItemTypes[static_cast<int>(ItemType::GreatSword)].SetSecondaryStat(SecondaryStats::Strength);
	myItemTypes[static_cast<int>(ItemType::GreatSword)].SetPrimeStatBuff(1);
	myItemTypes[static_cast<int>(ItemType::GreatSword)].SetSecondaryStatBuff(1);

	myItemTypes[static_cast<int>(ItemType::Helm)].SetItemType(ItemType::Helm);
	myItemTypes[static_cast<int>(ItemType::Helm)].SetItemSlot(ItemSlot::Helm);
	myItemTypes[static_cast<int>(ItemType::Helm)].SetWeight(5);
	myItemTypes[static_cast<int>(ItemType::Helm)].SetLevel(1);
	myItemTypes[static_cast<int>(ItemType::Helm)].SetPrimeStat(PrimeStats::Strength);
	myItemTypes[static_cast<int>(ItemType::Helm)].SetSecondaryStat(SecondaryStats::Strength);
	myItemTypes[static_cast<int>(ItemType::Helm)].SetPrimeStatBuff(1);
	myItemTypes[static_cast<int>(ItemType::Helm)].SetSecondaryStatBuff(1);

	myItemTypes[static_cast<int>(ItemType::Armor)].SetItemType(ItemType::Armor);
	myItemTypes[static_cast<int>(ItemType::Armor)].SetItemSlot(ItemSlot::Armor);
	myItemTypes[static_cast<int>(ItemType::Armor)].SetWeight(10);
	myItemTypes[static_cast<int>(ItemType::Armor)].SetLevel(1);
	myItemTypes[static_cast<int>(ItemType::Armor)].SetPrimeStat(PrimeStats::Strength);
	myItemTypes[static_cast<int>(ItemType::Armor)].SetSecondaryStat(SecondaryStats::Strength);
	myItemTypes[static_cast<int>(ItemType::Armor)].SetPrimeStatBuff(1);
	myItemTypes[static_cast<int>(ItemType::Armor)].SetSecondaryStatBuff(1);
}


int ItemFactory::RandomLevel() const
{
	int level = RandomNumber(1, 100);
	return level >= static_cast<int>(ItemBase::ProcentalChansLvlThree) ? 3 : level >= static_cast<int>(ItemBase::procentalChansLvlTwo) ? 2 : 1;
}

std::shared_ptr<Items> ItemFactory::CreateItem(const ItemType aItemType) const
{
	std::shared_ptr<Items> item = std::make_shared<Items>(myItemTypes[static_cast<int>(aItemType)]);
	return item;
}

std::shared_ptr<Items> ItemFactory::CreateItemWithRandomStats(const ItemType aItemType) const
{
	
	std::shared_ptr<Items> item = std::make_shared<Items>(myItemTypes[static_cast<int>(aItemType)]);
	item->SetLevel(RandomLevel());
	std::vector<PrimeStats> randomPrimeStat;
	std::vector<SecondaryStats> randomSecondaryStats;
	int buffDivider = RandomNumber(1, 5);
	switch (aItemType)
	{
	case ItemType::Dagger:
		{

			randomPrimeStat =
			{
				PrimeStats::Dexterety,
				PrimeStats::Charisma,
			};

			randomSecondaryStats =
			{
				SecondaryStats::Strength,
				SecondaryStats::Charisma,
				SecondaryStats::Damage,
				SecondaryStats::Persuasion,
				SecondaryStats::SlightOfHand
			};

			item->SetPrimeStat(randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))]);
			item->SetSecondaryStat(randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)]);
			item->SetPrimeStatBuff(RandomNumber(buffDivider, (buffDivider + 2)) * item->GetLevel());
			item->SetSecondaryStatBuff(RandomNumber(1, buffDivider) * item->GetLevel());
			break;
		}
	case ItemType::Sword:
	{

		randomPrimeStat =
		{
			PrimeStats::Dexterety,
			PrimeStats::Strength,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Dexterety,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp
		};


		item->SetPrimeStat(randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))]);
		item->SetSecondaryStat(randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)]);
		item->SetPrimeStatBuff(RandomNumber(buffDivider, (buffDivider + 2)) * item->GetLevel());
		item->SetSecondaryStatBuff(RandomNumber(1, buffDivider)* item->GetLevel());
		break;
	}
	case ItemType::GreatSword:
	{

		randomPrimeStat =
		{
			PrimeStats::Armor,
			PrimeStats::Strength,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Armor,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp,
			SecondaryStats::Athletics,
		};

		item->SetPrimeStat(randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))]);
		item->SetSecondaryStat(randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)]);
		item->SetPrimeStatBuff(RandomNumber(buffDivider, (buffDivider + 2)) * item->GetLevel());
		item->SetSecondaryStatBuff(RandomNumber(1, buffDivider) * item->GetLevel());
		break;
	}
	case ItemType::Helm:
	{

		randomPrimeStat =
		{
			PrimeStats::Charisma,
			PrimeStats::Dexterety,
			PrimeStats::Armor,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Charisma,
			SecondaryStats::Armor,
			SecondaryStats::MaxHp,
			SecondaryStats::Persuasion,
		};


		item->SetPrimeStat(randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))]);
		item->SetSecondaryStat(randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)]);
		item->SetPrimeStatBuff(RandomNumber(buffDivider, (buffDivider + 2)) * item->GetLevel());
		item->SetSecondaryStatBuff(RandomNumber(1, buffDivider)* item->GetLevel());
		break;
	}
	case ItemType::Armor:
	{

		randomPrimeStat =
		{
			PrimeStats::Strength,
			PrimeStats::Armor,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Armor,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp,
			SecondaryStats::Athletics,
		};

		item->SetPrimeStat(randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))]);
		item->SetSecondaryStat(randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)]);
		item->SetPrimeStatBuff(RandomNumber(buffDivider, (buffDivider + 2)) * item->GetLevel());
		item->SetSecondaryStatBuff(RandomNumber(1, buffDivider) * item->GetLevel());
		break;
	}
	default:
		break;
	}
	return item;

}

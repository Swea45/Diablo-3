#include "Player.h"
#include "Enums.h"
#include "Event.h"
#include "Quick functions.h"
#include "Items.h"
#include "Equipment.h"
#include "UI.h"
#include "Room.h"
#include <array>
#include <string>

Player::Player()
{
	myEquipment;
	myInventory;

	myStrength			= myBaseStrength;
	myDexterety			= myBaseDexterety;
	myDodge				= myBaseDodge;
	myCharisma			= myBaseCharisma;
	myArmor				= 0;
	myCurrentWeight		= 0;

	myHp				= (myStrength * 6) + (myDexterety * 3);
	myMaxHp				= myHp;
	myBaseDamage		= (myStrength * 2) + myDexterety;
	myCarryingCapacity	= (myStrength * 2) - myDodge;
	myAthletics			= myStrength + myDexterety;
	mySlightOfHand		= myDodge + myDexterety;
	myPersuasion		= myCharisma + myDodge;

	myIsAlive			= true;
	myCurrentRoomInt		= 0;
}

void Player::ChangeRoom(int aNewRoom)
{
	myCurrentRoomInt = aNewRoom;
}

void Player::FindPrimeStatBuff(PrimeStats aPrimeStat, int aStatBuff)
{
	switch (aPrimeStat)
	{
	case PrimeStats::Strength:
		myStrength += aStatBuff;
		break;

	case PrimeStats::Dexterety:
		myDexterety += aStatBuff;
		break;

	case PrimeStats::Charisma:
		myCharisma += aStatBuff;
		break;

	case PrimeStats::Armor:
		myArmor += aStatBuff;
		break;

	default:
		break;
	}
}
void Player::FindSecondaryStatBuff(SecondaryStats aSecondaryStat, int aStatBuff)
{
	switch (aSecondaryStat)
	{
	case SecondaryStats::Strength:
		myStrength += aStatBuff;
		break;

	case SecondaryStats::Dexterety:
		myDexterety += aStatBuff;
		break;

	case SecondaryStats::Charisma:
		myCharisma += aStatBuff;
		break;

	case SecondaryStats::MaxHp:
		myHp += aStatBuff;
		break;

	case SecondaryStats::Damage:
		myBaseDamage += aStatBuff;
		break;
	
	case SecondaryStats::Athletics:
		myAthletics += aStatBuff;
		break;

	case SecondaryStats::SlightOfHand:
		mySlightOfHand += aStatBuff;
		break;
	
	case SecondaryStats::Persuasion:
		myPersuasion += aStatBuff;
		break;

	case SecondaryStats::Armor:
		myArmor += aStatBuff;
		break;
	default:
		break;
	}
}
void Player::UppdatePlayerStats()
{
	float tempHp = static_cast<float>(myHp) / static_cast<float>(myMaxHp);


	myStrength = myBaseStrength;
	myDexterety = myBaseDexterety;
	myDodge = myBaseDodge;
	myCharisma = myBaseCharisma;

	myHp				= static_cast<int>(PlayerBase::ResetStats);
	myBaseDamage		= static_cast<int>(PlayerBase::ResetStats);
	myCarryingCapacity	= static_cast<int>(PlayerBase::ResetStats);
	myAthletics			= static_cast<int>(PlayerBase::ResetStats);
	mySlightOfHand		= static_cast<int>(PlayerBase::ResetStats);
	myPersuasion		= static_cast<int>(PlayerBase::ResetStats);
	myCurrentWeight		= static_cast<int>(PlayerBase::ResetStats);
	myArmor				= static_cast<int>(PlayerBase::ResetStats);


	if (myEquipment.GetEquipmentWeapon() != nullptr)
	{
		FindPrimeStatBuff(myEquipment.GetEquipmentWeapon()->GetPrimeStat(), myEquipment.GetEquipmentWeapon()->GetPrimeStatBuff()); 
		FindSecondaryStatBuff(myEquipment.GetEquipmentWeapon()->GetSecondaryStat(), myEquipment.GetEquipmentWeapon()->GetSecondaryStatBuff()); 
	}
	if (myEquipment.GetEquipmentHelm() != nullptr)
	{
		FindPrimeStatBuff(myEquipment.GetEquipmentHelm()->GetPrimeStat(), myEquipment.GetEquipmentHelm()->GetPrimeStatBuff());
		FindSecondaryStatBuff(myEquipment.GetEquipmentHelm()->GetSecondaryStat(), myEquipment.GetEquipmentHelm()->GetSecondaryStatBuff());

	}
	if (myEquipment.GetEquipmentArmor() != nullptr)
	{
		FindPrimeStatBuff(myEquipment.GetEquipmentArmor()->GetPrimeStat(), myEquipment.GetEquipmentArmor()->GetPrimeStatBuff());
		FindSecondaryStatBuff(myEquipment.GetEquipmentArmor()->GetSecondaryStat(), myEquipment.GetEquipmentArmor()->GetSecondaryStatBuff());

	}

	for (int i = 0; i < static_cast<int>(myEventEffects.size()); i++)
	{
		FindPrimeStatBuff(myEventEffects[i]->GetAffectedStat(), myEventEffects[i]->GetStatBuff());
	}

	for (int i = 0; i < static_cast<int>(myInventory.size()); i++)
	{
		myCurrentWeight += myInventory[i]->GetWeight();
	}

	myHp				+= (myStrength * 6) + (myDexterety * 3);
	myBaseDamage		+= (myStrength * 2) + myDexterety;
	myCarryingCapacity	+= (myStrength * 2) - myDodge;
	myAthletics			+= myStrength + myDexterety;
	mySlightOfHand		+= myDodge + myDexterety;
	myPersuasion		+= myCharisma + myDodge;

	myMaxHp = myHp;
	tempHp *= static_cast<float>(myHp);
	myHp = static_cast<int>(tempHp);

}

void Player::ShowPlayerStats()
{
	UppdatePlayerStats();
	int row = 1;
	ui::ClearArea(static_cast<int>(MenuOptions::StatsSeperatorX) + 1,
		static_cast<int>(MenuOptions::ScreenSeperatorY) + 1, 
		static_cast<int>(MenuOptions::FrameSizeEndX) - static_cast<int>(MenuOptions::StatsSeperatorX) - 2,
		static_cast<int>(MenuOptions::FrameSizeEndY) - static_cast<int>(MenuOptions::ScreenSeperatorY) - 2);
	ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	ui::Print("HP: " + std::to_string(myHp) + "/" + std::to_string(myMaxHp));
	row++;
	ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	ui::Print("Weight: " + std::to_string(myCurrentWeight) + "/" + std::to_string(myCarryingCapacity));
	row++;

	ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	ui::Print("STR: \t" + std::to_string(myStrength) + "\tCHA: \t" + std::to_string(myCharisma));
	row++;
	ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	ui::Print("DEX: \t" + std::to_string(myDexterety) + "\tDodge: \t" + std::to_string(myDodge));
	row++;
	ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	ui::Print("Armor: \t" + std::to_string(myArmor));
	row++;

	if (myEquipment.GetEquipmentWeapon() != nullptr)
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Weapon: \t" + ui::ToString(myEquipment.GetEquipmentWeapon()->GetItemType()));
	}
	else
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Weapon: \t No Weapon");
	}
	row++;

	if (myEquipment.GetEquipmentHelm() != nullptr)
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Helm: \t" + ui::ToString(myEquipment.GetEquipmentHelm()->GetItemType()));
	}
	else
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Helm: \t No Helm");
	}
	row++;

	if (myEquipment.GetEquipmentArmor() != nullptr)
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Armor: \t" + ui::ToString(myEquipment.GetEquipmentArmor()->GetItemType()));
	}
	else
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Armor: \t No Armor");
	}
}
void Player::AddEventEffects(std::shared_ptr<Event> aEventEffect)
{
	myEventEffects.push_back(aEventEffect);
}
const int Player::GetPlayerAbilityInt(PlayerBase anAbility)const
{
	switch (anAbility)
	{
		case PlayerBase::AthleticsSkill:
		{
			return myAthletics;
			break;
		}
		case PlayerBase::SlightOfHandSkill:
		{
			return mySlightOfHand;
			break;
		}
		case PlayerBase::PersuasionSkill:
		{
			return myPersuasion;
			break;
		}
	}
	return 0;
}

const int& Player::GetArmor()const
{
	return myArmor;
}
const int& Player::GetPlayerHp()const
{
	return myHp;
}
const int Player::GetNormalAttack()const
{
	int damage = DamageAdjustment(myBaseDamage);
	ui::PrintInMenu("You deal: " + std::to_string(damage) + " damage!");
	Sleep(1500);
	return damage;
}

void Player::UppdateHp(int aChange)
{
	int damageTaken = (aChange - myArmor) < 0 ? 0 : (aChange - myArmor);
	myHp -= damageTaken;
	if (myHp <= 0)
	{
		myIsAlive = false;
	}
}
bool Player::GetIsAlive()
{
	return myIsAlive;
}
const int& Player::GetCurrentRoom()const
{
	return myCurrentRoomInt;
}
std::string* Player::GetAbilityCheckList()
{
	return myAbilityChecks;
}

void Player::PickUpItem(std::shared_ptr<Items> aItem)
{
	myInventory.push_back(aItem);
}
std::vector<std::shared_ptr<Items>> Player::GetInventory()
{
	return myInventory;
}
void Player::EquipItem(int aItemChoise)
{
	switch (myInventory[aItemChoise]->GetItemSlot())
		{
		case ItemSlot::Weapon: 
		{
			myEquipment.SetEquipentWeapon(myInventory[aItemChoise]);
			break;
		}
		case ItemSlot::Helm:
		{
			myEquipment.SetEquipentHelm(myInventory[aItemChoise]);
			break;
		}
		case ItemSlot::Armor:
		{
			myEquipment.SetEquipentArmor(myInventory[aItemChoise]);
			break;
		}
		break;
	}
}
bool Player::CheckIsItemEquipt(std::shared_ptr<Items> aItem)
{
	if (aItem == myEquipment.GetEquipmentWeapon())
	{
		return true;
	}
	else if (aItem == myEquipment.GetEquipmentHelm())
	{
		return true;
	}
	else if (aItem == myEquipment.GetEquipmentArmor())
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Player::UnequipItem(std::shared_ptr<Items> aItem)
{
	if (aItem == myEquipment.GetEquipmentWeapon())
	{
		myEquipment.SetEquipentWeapon(nullptr);
	}
	else if (aItem == myEquipment.GetEquipmentHelm())
	{
		myEquipment.SetEquipentHelm(nullptr);
	}
	else if (aItem == myEquipment.GetEquipmentArmor())
	{
		myEquipment.SetEquipentArmor(nullptr);
	}
}
void Player::InventoryManagement()
{
	int playerChoiseInMenu = 0;
	while (true)
	{
		ShowPlayerStats();
		int playerTryPickUp = ui::ShowItems(myInventory, playerChoiseInMenu);
		if (playerTryPickUp >= myInventory.size())
		{
			return;
		}
		else
		{
			int itemChoise = 0;
			std::string choises[] = { "Equip","Unequip", "Drop", "Return" };
			ui::MenuControll(choises, 4, itemChoise);
			switch (itemChoise)
			{
			case 0:
			{
				EquipItem(playerTryPickUp);
				break;
			}
			case 1: 
			{
				if (CheckIsItemEquipt(myInventory[playerTryPickUp]))
				{
					UnequipItem(myInventory[playerTryPickUp]);
				}
				else
				{
					ui::PrintInMenu("This items isent equipt");
					Sleep(1000);
				}
				break;
			}
			case 2:
			{
				if (CheckIsItemEquipt(myInventory[playerTryPickUp]))
				{
					ui::PrintInMenu("You cant drop a Equipt Item");
					Sleep();
				}
				else
				{
					myCurrentRoomPtr->GiveItem(myInventory[playerTryPickUp]);
					myInventory.erase(myInventory.begin() + playerTryPickUp);
				}
				break;
			}
			default:
				break;
			}
			ui::ClearMenu();
		}
	}
}
const int& Player::GetInventoryWeight()const
{
	return myCurrentWeight;
}
const int& Player::GetCarryingCapacity()const
{
	return myCarryingCapacity;
}

void Player::ReduceTempBuffs()
{
	int removedEffects = 0;
	for (int i = 0; i < static_cast<int>(myEventEffects.size()); i++)
	{
		myEventEffects[i]->ReduceDuration();
		if (myEventEffects[i]->GetDuration() <= 0)
		{
			myEventEffects.erase(myEventEffects.begin() + i - removedEffects);
			removedEffects++;
		}
	}
}

void Player::SetRoomIndex(std::shared_ptr<Room> aRoom)
{
	myCurrentRoomPtr = aRoom;
}

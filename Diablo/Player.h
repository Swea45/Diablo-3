#pragma once
#include <string>
#include <array>
#include <vector>
#include "Enums.h"
#include "Equipment.h"
#include <memory>

class Items;
class Equipment;
class Event;
class Room;

class Player
{
public:
	Player();
	std::vector<std::shared_ptr<Items>> GetInventory();
	std::string* GetAbilityCheckList();
	const int& GetPlayerHp()const;
	const int GetNormalAttack()const;
	const int& GetCurrentRoom()const;
	const int GetPlayerAbilityInt(PlayerBase anAbility)const;
	const int& GetInventoryWeight()const;
	const int& GetCarryingCapacity()const;
	const int& GetArmor()const;
	bool GetIsAlive();
	void AddEventEffects(std::shared_ptr<Event> aEventEffect);
	void PickUpItem(std::shared_ptr<Items> aItem);
	void UppdateHp(int aChange);
	void ChangeRoom(int aNewRoom);
	void ShowPlayerStats();
	void InventoryManagement();
	void ReduceTempBuffs();
	void SetRoomIndex(std::shared_ptr<Room> aRoom);


private:
	Equipment myEquipment;
	std::vector<std::shared_ptr<Event>> myEventEffects;
	std::vector<std::shared_ptr<Items>> myInventory;
	std::string myAbilityChecks[static_cast<int>(PlayerBase::NumberOfPlayerAbilitys)] = { "Athletics", "Sleight of Hand", "Persuasion" };;
	std::shared_ptr<Room> myCurrentRoomPtr;
	int myCurrentRoomInt;
	bool CheckIsItemEquipt(std::shared_ptr<Items> aItem);
	void EquipItem(int aItemChoise);
	void UnequipItem(std::shared_ptr<Items> aItem);
	void UppdatePlayerStats();
	void FindPrimeStatBuff(PrimeStats aPrimeStat, int aStatBuff);
	void FindSecondaryStatBuff(SecondaryStats aSecondaryStat, int aStatBuff);
	
	const int myBaseStrength = static_cast<int>(PlayerBase::PlayerBaseStrength);
	const int myBaseDexterety = static_cast<int>(PlayerBase::PlayerBaseDexterety);
	const int myBaseDodge = static_cast<int>(PlayerBase::PlayerBaseDodge);
	const int myBaseCharisma = static_cast<int>(PlayerBase::PlayerBaseCharisma);
	const int myBaseArmor = static_cast<int>(PlayerBase::PlayerBaseArmor);

	int myStrength;
	int myDexterety;
	int myDodge;
	int myCharisma;
	int myArmor;

	int myHp;
	int myMaxHp;
	int myBaseDamage;
	int myCarryingCapacity;
	int myCurrentWeight;
	int myAthletics;
	int mySlightOfHand;
	int myPersuasion;

	bool myIsAlive;
};


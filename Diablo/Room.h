#pragma once
#include <vector>
#include "UI.h"
#include <array>
#include <memory>
#include "EnemyFactory.h"

class Chest;
class Event;
class Player;
class Enemy;
class Door;
class Items;
//class EnemyFactory;
class ItemFactory;

class Room
{
public:
	Room(int aRoomNr, std::string aRoomType);
	void Init(EnemyFactory& aEnemyFactory, ItemFactory& aItemFactory);
	void EnterRoom(Player& aPlayer, std::vector<std::shared_ptr<Door>> aListOfDoors, 
		std::vector<std::shared_ptr<Room>>& aRoomList, ItemFactory& aItemFactory);
	void SwitchRoom(Player& aPlayer, std::vector<std::shared_ptr<Room>>& aRoomList);
	const bool LastBossDefeted() const;
	const bool GetRoomExplored() const;
	std::string GetRoomName();
	void GiveItem(std::shared_ptr<Items> aItem);

private:

	std::vector<std::shared_ptr<Enemy>> myEnemyList;
	std::vector<std::shared_ptr<Items>> myItemList;
	std::vector<std::shared_ptr<Items>> myDroptLootList;
	std::vector<std::shared_ptr<Door>> myConnectingDoors;
	std::shared_ptr<Event> myEvent;
	std::shared_ptr<Chest> myChest;
	std::string myRoomType;
	std::string myRoomName;
	void RoomDescription();
	void CheckConnectingDoors(std::vector<std::shared_ptr<Door>> aListOfDoors);
	void CreateEnemys(EnemyFactory& aEnemyFactory, eEnemyTyps aEnemyType);
	void CreateItems(int aAmountOfItems, RoomBase aList, ItemFactory& aItemFactory);
	void Combat(Player& aPlayer, ItemFactory& aItemFactory);
	void Explore(Player& aPlayer);
	void Loot(Player& aPlayer);
	void RoomOptions(Player& aPlayer, std::vector<std::shared_ptr<Room>>& aRoomList);
	int myRoomNr;
	int myNumberOfEnemeis;
	bool LivingEnemies();
	bool myLastBossRoom;
	bool myLastBossDefeted;
	bool myRoomExplored;

};


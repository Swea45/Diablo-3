
#include <iostream>
#include <memory>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Room.h"
#include "Door.h"
#include "Quick functions.h"
#include "UI.h"
#include "EnemyFactory.h"
#include "ItemFactory.h"

void AddDoor(int aConnectingRoomOne, int aConnectingRoomTwo, std::vector<std::shared_ptr<Door>>& aListOfDoors)
{
	std::shared_ptr<Door> ptr = std::make_shared<Door>(aConnectingRoomOne, aConnectingRoomTwo);
	aListOfDoors.push_back(ptr);
}

void AddRoom(int aRoomNumber, std::string aRoomType, std::vector<std::shared_ptr<Room>>& aListOfRooms, 
	std::vector<std::shared_ptr<Door>>& aListOfDoors, EnemyFactory& aEnemyFactory, ItemFactory& aItemFactory)
{
	std::shared_ptr<Room> room = std::make_shared<Room>(aRoomNumber, aRoomType, aEnemyFactory, aItemFactory);
	aListOfRooms.push_back(room);
	if (aRoomType == "Start")
	{
		AddDoor(aRoomNumber, aRoomNumber++, aListOfDoors);
	}
	else if (aRoomType == "Normal")
	{
		AddDoor(aRoomNumber, aRoomNumber++, aListOfDoors);
	}
}

void CreateDungeon(std::vector<std::shared_ptr<Room>>& aListOfRooms,std::vector<std::shared_ptr<Door>>& aListOfDoors, 
	EnemyFactory& aEnemyFactory, ItemFactory& aItemFactory)
{
	for (int i = 0; i < static_cast<int>(RoomBase::NumberOfRooms); i++)
	{
		if (aListOfRooms.empty())
		{
			AddRoom(static_cast<int>(aListOfRooms.size()), "Start", aListOfRooms, aListOfDoors, aEnemyFactory, aItemFactory);
		}
		else if (i == static_cast<int>(RoomBase::NumberOfRooms) - 1)
		{
			AddRoom(static_cast<int>(aListOfRooms.size()), "Boss", aListOfRooms, aListOfDoors, aEnemyFactory, aItemFactory);
		}
		else
		{
			AddRoom(static_cast<int>(aListOfRooms.size()), "Normal", aListOfRooms, aListOfDoors, aEnemyFactory, aItemFactory);
		}
	}
}


int main()
{
	ui::SetCursorVisibility(false);
	ui::DrawFrame();
	std::vector<std::shared_ptr<Door>> doorsSmart;
	std::vector<std::shared_ptr<Room>> rooms;
	Player player;
	EnemyFactory enemyFactory;
	ItemFactory itemFactory;
	enemyFactory.Init();
	itemFactory.Init();



	CreateDungeon(rooms, doorsSmart, enemyFactory, itemFactory);

	player.ShowPlayerStats();
	while (player.GetIsAlive() == true && rooms[player.GetCurrentRoom()]->LastBossDefeted() == false)
	{
		player.SetRoomIndex(rooms[player.GetCurrentRoom()]);
		ui::ClearGame();
		rooms[player.GetCurrentRoom()]->EnterRoom(player, doorsSmart, rooms, itemFactory);
	}
	
	if (player.GetPlayerHp() <= 0)
	{
		ui::PrintInMenu("Hell is taking over after your defet!");
	}
	else
	{
		ui::PrintInMenu("You have defeted Diablo!");
	}
}


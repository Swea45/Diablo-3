#pragma once
#include <memory>
#include "Room.h"
#include "UI.h"
#include "Quick functions.h"
#include "Door.h"
#include "Enums.h"
#include "Player.h"
#include "Event.h"
#include "Chest.h"
#include "EnemyFactory.h"
#include "ItemFactory.h"


Room::Room(int aRoomNr, std::string aRoomType, EnemyFactory& aEnemyFactory, ItemFactory& aItemFactory)
{
	myEnemyList;
	myConnectingDoors;
	myItemList;
	myDroptLootList;
	
	myRoomType = aRoomType;
	myRoomNr = aRoomNr;
	myRoomName = " ? ? ? ";
	
	myRoomExplored = false;
	myLastBossRoom = false;
	myLastBossDefeted = false;
	myEvent = nullptr;

	if (myRoomType == "Random")
	{
		myRoomType = "Normal";
	}

	if (myRoomType == "Normal")
	{
		CreateEnemys(aEnemyFactory, eEnemyTyps::Normal);
		CreateItems(RandomNumber(static_cast<int>(RoomBase::MinNumberOfItemsDropt), static_cast<int>(RoomBase::MaxNumberOfItemsDropt)), RoomBase::ItemsExploreList, aItemFactory);
		myNumberOfEnemeis = static_cast<int>(myEnemyList.size());
		myRoomName = "Corridor";
		if (RandomNumber(0, static_cast<int>(RoomBase::ChansOfGettingAEvent)) == 0)
		{
			myEvent = std::make_shared<Event>();
		}

		if (RandomNumber(0, static_cast<int>(RoomBase::ChansOfGettingAChest)) == 0)
		{
			myChest = std::make_shared<Chest>();
		}
	}
	else if (myRoomType == "Boss")
	{

		myNumberOfEnemeis = static_cast<int>(myEnemyList.size());
		myLastBossRoom = true;
		myRoomName = "Boss Room";

	}
	else if (myRoomType == "Start")
	{
		CreateItems(RandomNumber(0, 1), RoomBase::ItemsExploreList, aItemFactory);
		myRoomName = "Entrance";

		if (RandomNumber(0, static_cast<int>(RoomBase::ChansOfGettingAEvent)) == 0)
		{
			myEvent = std::make_shared<Event>();
		}

		if (RandomNumber(0, static_cast<int>(RoomBase::ChansOfGettingAChest)) == 0)
		{
			myChest = std::make_shared<Chest>();
		}
	}
	
}


std::string Room::GetRoomName()
{
	return myRoomName;
}

const bool Room::GetRoomExplored() const
{
	return myRoomExplored;
}

const bool Room::LastBossDefeted() const
{
	return myLastBossDefeted;
}

void Room::CheckConnectingDoors(std::vector<std::shared_ptr<Door>> aListOfDoors)
{
	myConnectingDoors.clear();
	for (int i = 0; i < aListOfDoors.size(); i++)
	{
		if (aListOfDoors[i]->GetIsInCurrentRoom(myRoomNr) == true && myConnectingDoors.size() < static_cast<int>(DoorBase::maxDoorsInARoom))
		{
			myConnectingDoors.push_back(aListOfDoors[i]);
		}
	}
}

bool Room::LivingEnemies()
{
	bool livingEnemie = false;
	for (int i = 0; i < static_cast<int>(myEnemyList.size()); i++)
	{
		if (myEnemyList[i]->GetIsAlive() == true)
		{
			livingEnemie = true;
		}
	}
	return livingEnemie;
}

void Room::CreateEnemys(EnemyFactory& aEnemyFactory, eEnemyTyps aEnemyType)
{
	int numberOfEnemeis = RandomNumber(static_cast<int>(RoomBase::MinNumberOfEnemis), static_cast<int>(RoomBase::MaxNumberOfEnemis));
		for (int i = 0; i < numberOfEnemeis; i++)
		{
			myEnemyList.push_back(aEnemyFactory.CreateEnemyWithRandomStats(aEnemyType));
		}
}

void Room::CreateItems(int aAmountOfItems, RoomBase aList, ItemFactory& aItemFactory)
{
	std::vector<ItemType> randomItemType =
	{
		ItemType::Dagger,
		ItemType::Sword,
		ItemType::GreatSword,
		ItemType::Helm,
		ItemType::Armor,
	};
	aItemFactory;

	for (int i = 0; i < aAmountOfItems; i++)
	{
		aItemFactory.CreateItemWithRandomStats(randomItemType[RandomNumber(0, static_cast<int>(randomItemType.size()) - 1)]);
		if (aList == RoomBase::ItemsExploreList)
		{
			myItemList.push_back(aItemFactory.CreateItemWithRandomStats(randomItemType[RandomNumber(0, static_cast<int>(randomItemType.size()) - 1)]));
		}
		else if (aList == RoomBase::ItemsLootList)
		{
			myDroptLootList.push_back(aItemFactory.CreateItemWithRandomStats(randomItemType[RandomNumber(0, static_cast<int>(randomItemType.size()) - 1)]));
		}
	}
}

void Room::Combat(Player& aPlayer, ItemFactory& aItemFactory)
{
	ui::ClearMenu();
	int playerTarget = 0;
	while (aPlayer.GetIsAlive() == true && LivingEnemies() == true)
	{
		ui::ShowEnemy(myEnemyList);
		playerTarget = ui::ChoseEnemy(myEnemyList);
		if (myEnemyList[playerTarget]->UppdateHp(aPlayer.GetNormalAttack()))
		{
			if (RandomNumber(static_cast<int>(EnemyBase::DropItem), static_cast<int>(EnemyBase::DropItemChanse)) == static_cast<int>(EnemyBase::DropItem))
			{
				CreateItems(1, RoomBase::ItemsLootList, aItemFactory);
				ui::PrintInMenu("You hear something fall to the floor");
			}
		}
		
		ui::ShowEnemy(myEnemyList);
		Sleep();
		
		for (int i = 0; i < myNumberOfEnemeis; i++)
		{
			if (myEnemyList[i]->GetHp() > 0)
			{
				ui::PrintInMenu("The enemy is retaliating and attacking you!");
				aPlayer.UppdateHp(myEnemyList[i]->GetNormalAttack(aPlayer.GetArmor()));
				aPlayer.ShowPlayerStats();
			}
		}
	}


	aPlayer.ReduceTempBuffs();
	Sleep(1000);
	ui::ClearGame();
}

void Room::Explore(Player& aPlayer)
{
	if (myEvent != nullptr)
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::GameStartX), static_cast<int>(MenuOptions::GameStartY));
		ui::Print("You see somthing wierd in the room, do you wana interact with it?");
		ui::ClearMenu();
		
		switch (YesOrNo())
		{
		case true:
		{
			ui::PrintInMenu("You walk towards the object and tuch it...");
			Sleep();
			if (myEvent->GetIsInstant() == true)
			{
				ui::PrintInMenu(myEvent->GetEventDescription());
				Sleep();
				aPlayer.UppdateHp(myEvent->GetStatBuff());
			}
			else
			{
				ui::PrintInMenu(myEvent->GetEventDescription());
				Sleep();
				aPlayer.AddEventEffects(myEvent);
			}
			myEvent = nullptr;
			aPlayer.ShowPlayerStats();
			break;
		}
		case false:
		{
			ui::PrintInMenu("You chose to ignore it and search for some items instead");
			Sleep();
			break;
		}
		}
	}

	if (static_cast<int>(myItemList.size()) <= 0)
	{
		ui::PrintInMenu("You don't find any items in the room!");
		Sleep();
		return;
	}

	int playerChoiseInMenu = 0;
	while (true)
	{
		int playerTryPickUp = ui::ShowItems(myItemList, playerChoiseInMenu);
		if (playerTryPickUp >= myItemList.size())
		{
			return;
		}
		else
		{
			if (aPlayer.GetInventoryWeight() + myItemList[playerTryPickUp]->GetWeight() < aPlayer.GetCarryingCapacity())
			{
				aPlayer.PickUpItem(myItemList[playerTryPickUp]);
				myItemList.erase(myItemList.begin() + playerTryPickUp);
			}
			else
			{
				ui::PrintInMenu("You can't carry that much...");
				Sleep();
			}
		}
		aPlayer.ShowPlayerStats();
	}
}

void Room::Loot(Player& aPlayer)
{
	if (myChest != nullptr)
	{
		ui::PrintInMenu("You find a Chest!");
		Sleep();
		bool tryChest = true;
		while (tryChest)
		{
			ui::SetCursorPosition(static_cast<int>(MenuOptions::GameStartX), static_cast<int>(MenuOptions::GameStartY));
			ui::Print("Do you wana open the chest?");
			switch (YesOrNo())
			{
				case true:
				{
					ui::ClearGame();
					if (myChest->GetLockt() == true)
					{
						//Chest clost
						int playerMenuChoise = 0;
						ui::PrintInMenu("The chest is lockt...");
						Sleep();
						ui::MenuControll(aPlayer.GetAbilityCheckList(), static_cast<int>(PlayerBase::NumberOfPlayerAbilitys),
							playerMenuChoise);
						ui::ClearMenu();
						switch (playerMenuChoise)
						{
						case 0:
						{
							ui::PrintInMenu("You try to force the chest open...");
							Sleep();
							if (aPlayer.GetPlayerAbilityInt(PlayerBase::AthleticsSkill) > myChest->GetLockDifficultyStr())
							{
								ui::PrintInMenu("You crack the chest open!");
								Sleep();
								myChest->SetLockt(false);
							}
							else
							{
								ui::PrintInMenu("The chest stands firm, you arent strong enuth");
								Sleep();
							}
							break;
						}
						case 1:
						{
							ui::PrintInMenu("You try to pick the lock open... ");
							Sleep();
							if (aPlayer.GetPlayerAbilityInt(PlayerBase::SlightOfHandSkill) > myChest->GetLockDifficultyDex())
							{
								ui::PrintInMenu("You get the lock open!");
								Sleep();
								myChest->SetLockt(false);
							}
							else
							{
								ui::PrintInMenu("You can't get the lock to open");
								Sleep();
							}
							break;
						}
						case 2:
						{
							ui::PrintInMenu("You try to convins the chest to open...");
							Sleep();
							ui::PrintInMenu("It's a chest! It won't listen to your flattery nor reasoning");
							Sleep();
							break;
						}
						default:
							break;
						}
						break;
					}


					//Chest Open
					if (myChest->GetLockt() == false)
					{
						int playerChoiseInMenu = 0;
						bool lootingChest = true;
						while (lootingChest)
						{
							int playerTryPickUp = ui::ShowItems(myChest->GetInventory(), playerChoiseInMenu);
							if (playerTryPickUp >= myChest->GetInventorySize())
							{
								lootingChest = false;
								tryChest = false;
							}
							else
							{
								if (aPlayer.GetInventoryWeight() + myChest->GetInventory()[playerTryPickUp]->GetWeight() < aPlayer.GetCarryingCapacity())
								{
									aPlayer.PickUpItem(myChest->GetInventory()[playerTryPickUp]);
									myChest->RemoveItem(playerTryPickUp);
								}
								else
								{
									ui::PrintInMenu("You can't carry that much...");
									Sleep();
								}
							}
							aPlayer.ShowPlayerStats();
						}
					}
					if (myChest->GetInventorySize() <= 0)
					{
						myChest = nullptr;
					}
					ui::ClearGame();
					break;
				case false:
				{
					ui::ClearGame();
					ui::PrintInMenu("You pass the chest to search the monsters for loot!");
					Sleep();
					tryChest = false;
					break;
				}
				}
			}
		}
	}

	if (static_cast<int>(myDroptLootList.size()) <= 0)
	{
		ui::PrintInMenu("You don't find anything on the monster!");
		Sleep();
		return;
	}

	ui::PrintInMenu("You find some items on the monsters!");
	Sleep();

	int playerChoiseInMenu = 0;
	while (true)
	{
		int playerTryPickUp = ui::ShowItems(myDroptLootList, playerChoiseInMenu);
		if (playerTryPickUp >= myDroptLootList.size())
		{
			return;
		}
		else
		{
			if (aPlayer.GetInventoryWeight() + myDroptLootList[playerTryPickUp]->GetWeight() < aPlayer.GetCarryingCapacity())
			{
				aPlayer.PickUpItem(myDroptLootList[playerTryPickUp]);
				myDroptLootList.erase(myDroptLootList.begin() + playerTryPickUp);
			}
			else
			{
				ui::PrintInMenu("You can't carry that much...");
				Sleep();
			}
		}
		aPlayer.ShowPlayerStats();
	}
}

void Room::SwitchRoom(Player& aPlayer, std::vector<std::shared_ptr<Room>>& aRoomList)
{
	while (true)
	{

		int doorTry = ui::ShowDoors(myConnectingDoors, aRoomList, myRoomNr);
		if (myConnectingDoors[doorTry]->GetDoorLockt() == true)
		{
			int playerMenuChoise = 0;
			ui::PrintInMenu("The door is lockt...");
			Sleep();
			ui::MenuControll(aPlayer.GetAbilityCheckList(), static_cast<int>(PlayerBase::NumberOfPlayerAbilitys), playerMenuChoise);
			ui::ClearMenu();
			switch (playerMenuChoise)
			{
				case static_cast<int>(PlayerBase::AthleticsSkill):
				{
					ui::PrintInMenu("You try to break the door open...");
					Sleep(1500);
					if ((aPlayer.GetPlayerAbilityInt(PlayerBase::AthleticsSkill) + RandomNumber(1, 20)) > myConnectingDoors[doorTry]->GetLockDifficultyStr())
					{
						myConnectingDoors[doorTry]->SetDoorLockt(false);
						ui::PrintInMenu("You break the door open and can walk through");
						Sleep();
						aPlayer.ChangeRoom(myConnectingDoors[doorTry]->GetConnectingRoom(myRoomNr));
						return;
					}
					else
					{
						ui::PrintInMenu("The door isn't budging");
						Sleep();
					}
					break;
				}
				case static_cast<int>(PlayerBase::SlightOfHandSkill):
				{
					ui::PrintInMenu("You try to pick the lock...");
					Sleep(1500);
					if ((aPlayer.GetPlayerAbilityInt(PlayerBase::SlightOfHandSkill) + RandomNumber(1, 20)) > myConnectingDoors[doorTry]->GetLockDifficultyDex())
					{
						ui::PrintInMenu("The lock opens and you can walk through");
						Sleep();
						myConnectingDoors[doorTry]->SetDoorLockt(false);
						aPlayer.ChangeRoom(myConnectingDoors[doorTry]->GetConnectingRoom(myRoomNr));
						return;
					}
					else
					{
						ui::PrintInMenu("You can't find a way to open the lock");
					}
					break;
				}
				case static_cast<int>(PlayerBase::PersuasionSkill):
				{
					ui::PrintInMenu("You try to convins the door to open...");
					Sleep();

					if (RandomNumber(1, 20) == 20)
					{
						ui::PrintInMenu("The door opens...");
						Sleep();
						ui::PrintInMenu("You're not quite sure how...");
						Sleep();
						ui::PrintInMenu("You choose to take the chance to go through!");
						myConnectingDoors[doorTry]->SetDoorLockt(false);
						aPlayer.ChangeRoom(myConnectingDoors[doorTry]->GetConnectingRoom(myRoomNr));
						return;
					}
					else
					{
						ui::PrintInMenu("It looks like it's not working");
						Sleep();
						break;
					}
				}
			default:
				break;
			}
		}
		else if (myConnectingDoors[doorTry]->GetDoorLockt() == false)
		{
			aPlayer.ChangeRoom(myConnectingDoors[doorTry]->GetConnectingRoom(myRoomNr));
			return;
		}
	}
}

void Room::GiveItem(std::shared_ptr<Items> aItem)
{
	myItemList.push_back(aItem);
}

void Room::RoomOptions(Player& aPlayer, std::vector<std::shared_ptr<Room>>& aRoomList)
{
	std::string roomOptions[] = { "Explore", "Loot", "Inventory", "Switch Room"};
	int playerChoise = 0;
	
	while (true)
	{
		aPlayer.ShowPlayerStats();
		ui::MenuControll(roomOptions, static_cast<int>(size(roomOptions)), playerChoise);
		ui::ClearMenu();
		ui::ClearGame();
		switch (playerChoise)
		{
			case static_cast<int>(RoomBase::MenuExplore):
			{
				Explore(aPlayer);
				break;
			}
			case static_cast<int>(RoomBase::MenuLoot):
			{
				Loot(aPlayer);
				break;
			}
			case static_cast<int>(RoomBase::MenuInventory):
			{
				aPlayer.InventoryManagement();
				break;
			}
			case static_cast<int>(RoomBase::MenuSwitchRoom):
			{
				SwitchRoom(aPlayer, aRoomList);
				return;
				break;
			}
		}
	}
}

void Room::RoomDescription()
{
	if (myRoomName == "Entrance")
	{
		ui::PrintInMenu("You are in the entrance of the dungeon, the path to the surface is blockt!");
	}
	else if (myRoomName == "Corridor")
	{
		ui::PrintInMenu("It is a long and dark corridor, you can hear something up ahead...");
	}
	else if (myRoomName == "Boss Room")
	{
		ui::PrintInMenu("You feel like something big might jump at you...");
	}
}

void Room::EnterRoom(Player& aPlayer, std::vector<std::shared_ptr<Door>> aListOfDoors, std::vector<std::shared_ptr<Room>>& aRoomList, 
	ItemFactory& aItemFactory)
{

	RoomDescription();
	Sleep();
	myRoomExplored = true;
	if (LivingEnemies())
	{
		Combat(aPlayer, aItemFactory);
		ui::ClearGame();
		ui::PrintInMenu("All enemys have been defeted...");
		Sleep(1000);
	}

	if (myChest != nullptr)
	{
		myChest->Init(aItemFactory);
	}

	if (myLastBossRoom == true && aPlayer.GetIsAlive() == true)
	{
		myLastBossDefeted = true;
		return;
	}
	else if (aPlayer.GetIsAlive() == true)
	{
		CheckConnectingDoors(aListOfDoors);
		RoomOptions(aPlayer, aRoomList);
	}
}
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Enums.h"
#include "Door.h"
#include "Room.h"
#include "Items.h"

class Room;
class Door;

namespace ui
{
	void DrawFrame();
	void MenuControll(std::string aMenuList[], int aMenuSize, int& aPlayerChoiseInMenu);
	int ShowItems(std::vector<std::shared_ptr<Items>> aListOfItems, int& playerChoiseInMenu);
	void PrintDoorSprite(int aStartX, int aStartY, bool aTarget, bool aRoomExplored, std::string aRoomName);
	void ShowEnemy(std::vector<std::shared_ptr<Enemy>> aList);
	int ShowDoors(std::vector<std::shared_ptr<Door>> aVectorOfDoors, std::vector<std::shared_ptr<Room>>& aVectorOfRooms, int aCurrentRoom);
	int ChoseEnemy(std::vector<std::shared_ptr<Enemy>>  aList);
	void Print(std::string aString);
	void PrintInMenu(std::string aString);
	void ClearArea(int anX, int anY, int aXLength, int aYLength = 1);
	void ClearGame();
	void ClearMenu();
	void SetColor(ColorInt aColor);
	void SetCursorPosition(int aX, int aY);
	void SetCursorVisibility(bool aSetCursor);
	std::string ToString(ItemType aItem);
	std::string ToString(PrimeStats aPrimeStat);
	std::string ToString(SecondaryStats aSecondaryStat);
}
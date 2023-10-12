#include "Door.h"
#include "Quick functions.h"

Door::Door(int aRoomOne, int aRoomTwo)
{
	myConnectingRoomOne = aRoomOne;
	myConnectingRoomTwo = aRoomTwo;
	myLockDifficultyStr = 0;
	myLockDifficultyDex = 0;
	myDoorLockt = RandomNumber(0, 1) == 1 ? true : false;
	if (myDoorLockt == true)
	{
		myLockDifficultyStr = RandomNumber(20, 40);
		myLockDifficultyDex = RandomNumber(20, 30);
	}
}

int Door::GetLockDifficultyStr()
{
	return myLockDifficultyStr;
}

int Door::GetLockDifficultyDex()
{
	return myLockDifficultyDex;
}

int Door::GetConnectingRoom(int aCurrentRoom)
{
	if (aCurrentRoom == myConnectingRoomOne)
	{
		return myConnectingRoomTwo;
	}
	else if (aCurrentRoom == myConnectingRoomTwo)
	{
		return myConnectingRoomOne;
	}
	
	return -1;
}


bool Door::GetIsInCurrentRoom(int aCurrentRoom)
{
	return (aCurrentRoom == myConnectingRoomOne || aCurrentRoom == myConnectingRoomTwo);
}

bool Door::GetDoorLockt()
{
	return myDoorLockt;
}
void Door::SetDoorLockt(bool aDoorLockt)
{
	myDoorLockt = aDoorLockt;
}
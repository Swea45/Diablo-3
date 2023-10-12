#pragma once
class Room;

class Door
{
public:
	Door(int aRoomOne, int aRoomTwo);
	int GetConnectingRoom(int aCurrentRoom);
	int GetLockDifficultyStr();
	int GetLockDifficultyDex();
	bool GetIsInCurrentRoom(int aCurrentRoom);
	bool GetDoorLockt();
	void SetDoorLockt(bool aDoorLockt);


private:
	int myConnectingRoomOne;
	int myConnectingRoomTwo;
	int myLockDifficultyStr;
	int myLockDifficultyDex;
	bool myDoorLockt;
};


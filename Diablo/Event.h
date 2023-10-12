#pragma once
#include "Enums.h"
#include <string>

class Event
{
public:
	Event();
	std::string GetEventDescription();
	PrimeStats GetAffectedStat();
	int GetStatBuff();
	int GetDuration();
	bool GetIsInstant();
	void ReduceDuration();


private:
	void SetRandomEvent();
	void Shrine();
	void Poison();
	void Trap();
	std::string myEventDescription;
	EventNames myEventName;
	PrimeStats myAffectedStat;
	int myStatBuff;
	int myDuration;
	bool myIsInstant;
};


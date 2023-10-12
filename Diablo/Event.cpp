#include "Event.h"
#include "Enums.h"
#include "Quick functions.h"
#include "UI.h"
#include <string>

Event::Event()
{
	myEventName;
	myAffectedStat;
	myStatBuff;
	myEventDescription;
	myIsInstant;
	myDuration = RandomNumber(static_cast<int>(EventBase::MinDuration), static_cast<int>(EventBase::MaxDuration));
	SetRandomEvent();
}

void Event::SetRandomEvent()
{
	switch (RandomNumber(1, 4)) 
	{
		case 1: 
		{
			Shrine();
			break;
		}
		case 2: 
		{
			Shrine();
			break;
		}
		case 3:
		{
			Poison();
			break;
		}
		case 4:
		{
			Trap();
			break;
		}
	}
}

void Event::Shrine()
{
	myIsInstant = false;
	myEventName = EventNames::Shrine;
	std::vector<PrimeStats> randomPrimeStat = {
	PrimeStats::Strength,
	PrimeStats::Dexterety,
	PrimeStats::Charisma,
	PrimeStats::Armor,
	};

	myStatBuff = RandomNumber(5, 10);
	myAffectedStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
	myEventDescription = "You feel a growing light inside of you. Your " + ui::ToString(myAffectedStat) + " has improved!";
}

void Event::Poison()
{
	myIsInstant = false;
	myEventName = EventNames::Poison;
	std::vector<PrimeStats> randomPrimeStat = {
	PrimeStats::Strength,
	PrimeStats::Dexterety,
	PrimeStats::Charisma,
	};

	
	myStatBuff = -RandomNumber(5, 10);
	myAffectedStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
	myEventDescription = "You have been poisoned. Your " + ui::ToString(myAffectedStat) + " has deteriorated!";
}

void Event::Trap()
{
	myIsInstant = true;
	myEventName = EventNames::Trap;
	myAffectedStat = PrimeStats::Hp;
	bool dodge = RandomNumber(0, 1) == 1 ? true : false;
	if (dodge)
	{
		myStatBuff = 0;
		myEventDescription = "There is a trap! You dodge it without taking any damage!";
	}
	else
	{
		myStatBuff = RandomNumber(10, 30);
		myEventDescription = "There is a trap! You get hit and take " + std::to_string(myStatBuff) + " damge!";
	}
}

std::string Event::GetEventDescription()
{
	return myEventDescription;
}

PrimeStats Event::GetAffectedStat()
{
	return myAffectedStat;
}

int Event::GetStatBuff()
{
	return myStatBuff;
}

void Event::ReduceDuration()
{
	myDuration--;
}

int Event::GetDuration()
{
	return myDuration;
}

bool Event::GetIsInstant()
{
	return myIsInstant;
}
#pragma once
enum class PlayerBase
{
	PlayerBaseStrength		= 15,
	PlayerBaseDexterety		= 10,
	PlayerBaseCharisma		= 12,
	PlayerBaseDodge			= 5,
	NumberOfPlayerAbilitys	= 3,
	PlayerBaseArmor			= 1,
	PlayerLivingState		= true,
	ResetStats				= 0,

	AthleticsSkill			= 0,
	SlightOfHandSkill		= 1,
	PersuasionSkill			= 2,
};


enum class EnemyBase
{
	DropItem				= 0,
	DropItemChanse			= 3,
};

enum class RoomBase
{
	MaxNumberOfEnemis		= 3,
	MinNumberOfEnemis		= 1,
	
	MaxNumberOfItemsDropt	= 2,
	MinNumberOfItemsDropt	= 0,

	ChansOfGettingAEvent	= 2, 
	ChansOfGettingAChest	= 2,

	MenuExplore				= 0,
	MenuLoot				= 1,
	MenuInventory			= 2,
	MenuSwitchRoom			= 3,
	
	ItemsExploreList,
	ItemsLootList,

	NumberOfRooms			= 4,

};

enum class DoorBase
{
	doorSpriteSizeX			= 16,
	maxDoorsInARoom			= 4
};

enum class ItemBase
{
	ProcentalChansLvlThree	= 80,
	procentalChansLvlTwo	= 50,
};

enum class EventBase
{
	MaxDuration				= 1,
	MinDuration				= 1,
};

enum class ChestBase
{
	MinLockDifficulty		= 15,
	MaxLockDifficulty		= 40,
	
	MinAmountOfItems		= 1,
	MaxAmountOfItems		= 3,

	Lock					= 0,
	LockChans				= 2,

};

enum class MenuOptions
{
	MenuListUp				= 1,
	MenuListDown			= 2,
	MenuListLeft			= 3,
	MenuListRight			= 4,
	MenuListOption			= 0,

	FrameSizeStartY			= 0,
	FrameSizeStartX			= 0,
	FrameSizeEndX			= 100,
	FrameSizeEndY			= 27,
	ScreenSeperatorY		= FrameSizeEndY - 10,
	StatsSeperatorX			= FrameSizeEndX - 30,
	ItemStatsPrimeStartX	= FrameSizeEndX - 70,
	ItemStatsSecondaryStartX= ItemStatsPrimeStartX + 17,
	
	GameStartY				= FrameSizeStartY + 1,
	GameStartX				= FrameSizeStartX + 1,
	
	MenyStartY				= ScreenSeperatorY + 1,
	MenyStartX				= FrameSizeStartX + 1,

};


enum class ColorInt
{
	WhiteColorText			= 0,
	GreenColorText			= 1,
	RedColorText			= 2,
	LightGrayColorText		= 3,
};

enum class ExtraInts
{
	SleepStandardTime		= 2000,
	OfSet					= 3,
	
};

enum class ItemType
{
	Dagger,
	Sword,
	GreatSword,
	Helm,
	Armor,

	count,
};

enum class PrimeStats
{
	Strength,
	Dexterety,
	Charisma,
	Armor,
	Hp,
};

enum class SecondaryStats
{
	Strength,
	Dexterety,
	Charisma,
	MaxHp,
	Damage,
	Athletics,
	SlightOfHand,
	Persuasion,
	Armor,
};

enum class ItemSlot
{
	Helm,
	Armor,
	Weapon,
};

enum class EventNames
{
	Shrine,
	Poison,
	Trap,
};

enum class eEnemyTyps
{
	Normal,
	Boss,



	count,
};
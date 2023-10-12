#include "UI.h"
#include "Quick functions.h"
#include <Windows.h>
#include <vector>
#include "Enemy.h"
#include "Door.h"
#include "Room.h"
#include "Enums.h"
#include "Items.h"

namespace ui
{

	void Print(std::string aString)
	{
		std::cout << aString << std::endl;
	}
	void PrintInMenu(std::string aString)
	{
		ClearMenu();
		int row = 0;
		std::string printOutStringPart = aString;
		std::string tempString;


		while (printOutStringPart.size() > static_cast<int>(MenuOptions::StatsSeperatorX) - 2)
		{
			if (aString.size() > static_cast<int>(MenuOptions::StatsSeperatorX) - 2)
			{
				std::string::size_type split = printOutStringPart.rfind(' ', static_cast<int>(MenuOptions::StatsSeperatorX) - 2);
				ui::SetCursorPosition(static_cast<int>(MenuOptions::MenyStartX), static_cast<int>(MenuOptions::MenyStartY) + row);
				std::cout << printOutStringPart.substr(0, split) << std::endl;
				printOutStringPart.erase(0, split + 1);
				row++;
			}
		}

		ui::SetCursorPosition(static_cast<int>(MenuOptions::MenyStartX), static_cast<int>(MenuOptions::MenyStartY) + row);
		std::cout << printOutStringPart << std::endl;
	}


	void ClearArea(int anX, int anY, int aXLength, int aYLength)
	{
		for (int y = 0; y < aYLength; y++)
		{
			for (int x = 0; x < aXLength; x++)
			{
				ui::SetCursorPosition(anX + x, anY + y);
				Print(" ");
			}
		}

	}
	void ClearGame()
	{
		for (int y = 1; y < static_cast<int>(MenuOptions::ScreenSeperatorY); y++)
		{
			SetCursorPosition(1, y);
			std::cout << "                                                                                                  ";

		}
		std::cout << std::endl;
	}
	void ClearMenu()
	{
		for (int y = static_cast<int>(MenuOptions::ScreenSeperatorY) + 1; y < static_cast<int>(MenuOptions::FrameSizeEndY) - 1; y++)
		{
			ui::SetCursorPosition(1, y);
			std::cout << "                                                                     ";
		}
	}

	void SetColor(ColorInt aColor)
	{
		switch (aColor)
		{
		case ColorInt::GreenColorText:
		{
			std::cout << "\x1B[32m";
			break;
		}
		case ColorInt::WhiteColorText:
		{
			std::cout << "\x1B[37m";
			break;
		}
		case ColorInt::RedColorText:
		{
			std::cout << "\x1B[31m";
			break;
		}
		case ColorInt::LightGrayColorText:
		{
			std::cout << "\x1B[90m";
			break;
		}
		default:
		{
			std::cout << "\x1B[37m";
			break;
		}
		}
	}
	void SetCursorPosition(int aX, int aY)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)aX, (SHORT)aY };
		SetConsoleCursorPosition(hConsole, coord);
	}

	void DrawFrame()
	{
		SetCursorPosition(0, 0);
		for (int y = 0; y < static_cast<int>(MenuOptions::FrameSizeEndY); y++)
		{
			for (int x = 0; x < static_cast<int>(MenuOptions::FrameSizeEndX); x++)
			{
				if (y == static_cast<int>(MenuOptions::FrameSizeStartY) || y == static_cast<int>(MenuOptions::FrameSizeEndY) - 1 || y == static_cast<int>(MenuOptions::ScreenSeperatorY))
				{
					SetCursorPosition(x, y);
					std::cout << "-";
				}
				else if (x == static_cast<int>(MenuOptions::FrameSizeStartX) || x == static_cast<int>(MenuOptions::FrameSizeEndX) - 1)
				{
					SetCursorPosition(x, y);
					std::cout << "|";
				}
				else if (x == static_cast<int>(MenuOptions::StatsSeperatorX) && y > static_cast<int>(MenuOptions::ScreenSeperatorY) && y < static_cast<int>(MenuOptions::FrameSizeEndY))
				{
					SetCursorPosition(x, y);
					std::cout << "|";

				}
			}
		}
		std::cout << std::endl;
	}

	void MenuControll(std::string aMenuList[], int aMenuSize, int& aPlayerChoiseInMenu)
	{
		while (true)
		{
			ClearMenu();
			SetCursorPosition(static_cast<int>(MenuOptions::MenyStartX), static_cast<int>(MenuOptions::MenyStartY));
			for (int i = 0; i < aMenuSize; ++i)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_SCREEN_BUFFER_INFO csbi;

				if (GetConsoleScreenBufferInfo(hConsole, &csbi))
				{
					COORD cursorPosition = csbi.dwCursorPosition;
					int x = cursorPosition.X + 1;
					int y = cursorPosition.Y;
					SetCursorPosition(x, y);
				}
				if (i == aPlayerChoiseInMenu)
				{
					SetColor(ColorInt::GreenColorText);
					std::cout << "\t" << aMenuList[i] << "\t <---" << std::endl;
				}
				else
				{

					SetColor(ColorInt::WhiteColorText);
					std::cout << aMenuList[i] << std::endl;
				}
			}
			SetColor(ColorInt::WhiteColorText);
			switch (ButtonPress())
			{
			case MenuOptions::MenuListUp:
			{
				if (aPlayerChoiseInMenu > 0)
				{
					aPlayerChoiseInMenu--;
				}
				else
				{
					aPlayerChoiseInMenu = aMenuSize - 1;
				}
				break;
			}
			case MenuOptions::MenuListDown:
			{
				if (aPlayerChoiseInMenu < aMenuSize - 1)
				{
					aPlayerChoiseInMenu++;
				}
				else
				{
					aPlayerChoiseInMenu = 0;
				}
				break;
			}
			case MenuOptions::MenuListOption:
			{
				return;
				break;
			}
			}
		}
	}

	int ShowItems(std::vector<std::shared_ptr<Items>> aListOfItems, int& aPlayerChoiseInMenu)
	{
		if (aPlayerChoiseInMenu > static_cast<int>(aListOfItems.size()))
		{
			aPlayerChoiseInMenu--;
		}
		while (true)
		{

			int x;
			int y;

			ClearGame();
			SetCursorPosition(static_cast<int>(MenuOptions::GameStartX), static_cast<int>(MenuOptions::GameStartX) + 1);
			for (int i = 0; i < static_cast<int>(aListOfItems.size()); ++i)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_SCREEN_BUFFER_INFO csbi;

				if (GetConsoleScreenBufferInfo(hConsole, &csbi))
				{
					COORD cursorPosition = csbi.dwCursorPosition;
					x = cursorPosition.X + 1;
					y = cursorPosition.Y;
					SetCursorPosition(x, y);
				}

				if (i == aPlayerChoiseInMenu)
				{
					SetColor(ColorInt::GreenColorText);
					std::cout << "\t" << ui::ToString(aListOfItems[i]->GetItemType()) << " <---";
					SetColor(ColorInt::WhiteColorText);

					if (GetConsoleScreenBufferInfo(hConsole, &csbi))
					{
						COORD cursorPosition = csbi.dwCursorPosition;
						x = static_cast<int>(MenuOptions::ItemStatsPrimeStartX);
						y = cursorPosition.Y;
						SetCursorPosition(x, y);
					}
					std::cout << ui::ToString(aListOfItems[i]->GetPrimeStat()) << ": +" << aListOfItems[i]->GetPrimeStatBuff();

					if (GetConsoleScreenBufferInfo(hConsole, &csbi))
					{
						COORD cursorPosition = csbi.dwCursorPosition;
						x = static_cast<int>(MenuOptions::ItemStatsSecondaryStartX);
						y = cursorPosition.Y;
						SetCursorPosition(x, y);
					}
					std::cout << ui::ToString(aListOfItems[i]->GetSecondaryStat()) << ": +" << aListOfItems[i]->GetSecondaryStatBuff() << std::endl;
				}
				else
				{

					SetColor(ColorInt::WhiteColorText);
					std::cout << ui::ToString(aListOfItems[i]->GetItemType());

					if (GetConsoleScreenBufferInfo(hConsole, &csbi))
					{
						COORD cursorPosition = csbi.dwCursorPosition;
						x = static_cast<int>(MenuOptions::ItemStatsPrimeStartX);
						y = cursorPosition.Y;
						SetCursorPosition(x, y);
					}
					std::cout << ui::ToString(aListOfItems[i]->GetPrimeStat()) << ": +" << aListOfItems[i]->GetPrimeStatBuff();

					if (GetConsoleScreenBufferInfo(hConsole, &csbi))
					{
						COORD cursorPosition = csbi.dwCursorPosition;
						x = static_cast<int>(MenuOptions::ItemStatsSecondaryStartX);
						y = cursorPosition.Y;
						SetCursorPosition(x, y);
					}
					std::cout << ui::ToString(aListOfItems[i]->GetSecondaryStat()) << ": +" << aListOfItems[i]->GetSecondaryStatBuff() << std::endl;

				}
			}

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			if (GetConsoleScreenBufferInfo(hConsole, &csbi))
			{
				COORD cursorPosition = csbi.dwCursorPosition;
				x = cursorPosition.X + 1;
				y = cursorPosition.Y;
				SetCursorPosition(x, y);
			}

			if (aPlayerChoiseInMenu == static_cast<int>(aListOfItems.size()))
			{
				SetColor(ColorInt::GreenColorText);
				std::cout << "\tReturn  <---" << std::endl;
			}
			else
			{
				SetColor(ColorInt::WhiteColorText);
				std::cout << "Return" << std::endl;

			}
			SetColor(ColorInt::WhiteColorText);

			switch (ButtonPress())
			{
			case MenuOptions::MenuListUp:
			{
				if (aPlayerChoiseInMenu > 0)
				{
					aPlayerChoiseInMenu--;
				}
				else
				{
					aPlayerChoiseInMenu = static_cast<int>(aListOfItems.size());
				}
				break;
			}
			case MenuOptions::MenuListDown:
			{
				if (aPlayerChoiseInMenu < static_cast<int>(aListOfItems.size()))
				{
					aPlayerChoiseInMenu++;
				}
				else
				{
					aPlayerChoiseInMenu = 0;
				}
				break;
			}
			case MenuOptions::MenuListOption:
			{
				return aPlayerChoiseInMenu;
				break;
			}
			}
		}
	}

	void ShowEnemy(std::vector<std::shared_ptr<Enemy>> aList)
	{
		ClearGame();
		int ofSetX = 3;
		for (int i = 0; i < aList.size(); i++)
		{
			if (aList[i]->GetIsAlive() == true)
			{
				aList[i]->PrintEnemySprite(static_cast<int>(MenuOptions::GameStartX) + ofSetX, static_cast<int>(MenuOptions::GameStartY) + 2);
				ofSetX += aList[i]->GetSpriteSizeX() + 10;
			}
			else
			{
				ofSetX += aList[i]->GetSpriteSizeX() + 10;
			}

		}
	}

	int ChoseEnemy(std::vector<std::shared_ptr<Enemy>> aList)
	{
		bool missingTarget = true;
		int playerChoise = 0;
		while (true)
		{
			int ofSetX = 3;
			ClearArea(static_cast<int>(MenuOptions::GameStartX) + ofSetX, static_cast<int>(MenuOptions::GameStartY), static_cast<int>(MenuOptions::FrameSizeEndX) - ofSetX);
			for (int i = 0; i < aList.size(); i++)
			{
				if (i == playerChoise)
				{
					aList[i]->ShowTarget(static_cast<int>(MenuOptions::GameStartX) + ofSetX, static_cast<int>(MenuOptions::GameStartY) + 2, true);

				}
				else
				{
					aList[i]->ShowTarget(static_cast<int>(MenuOptions::GameStartX) + ofSetX, static_cast<int>(MenuOptions::GameStartY) + 2, false);
				}
				ofSetX += aList[i]->GetSpriteSizeX() + 10;

			}

			switch (ButtonPress())
			{
			case MenuOptions::MenuListLeft:
			{
				if (playerChoise > 0)
				{
					playerChoise--;
				}
				else
				{
					playerChoise = static_cast<int>(aList.size()) - 1;
				}
				break;
			}
			case MenuOptions::MenuListRight:
			{
				if (playerChoise < static_cast<int>(aList.size()) - 1)
				{
					playerChoise++;
				}
				else
				{
					playerChoise = 0;
				}
				break;
			}
			case MenuOptions::MenuListOption:
			{
				if (aList[playerChoise]->GetIsAlive() == true)
				{
					return playerChoise;
				}
				else
				{
					if (missingTarget == true)
					{
						ClearMenu();
						PrintInMenu("There is no monster there, try again!");
						Sleep();
						missingTarget = false;
					}

				}
				break;
			}
			}
		}
	}

	int ShowDoors(std::vector<std::shared_ptr<Door>> aVectorOfDoors, std::vector<std::shared_ptr<Room>>& aVectorOfRooms, int aCurrentRoom)
	{
		int playerChoise = 0;

		while (true)
		{
			int extraSpace = 0;
			ClearGame();

			for (int i = 0; i < aVectorOfDoors.size(); i++)
			{
				if (i == playerChoise)
				{
					PrintDoorSprite(static_cast<int>(MenuOptions::GameStartX) + static_cast<int>(ExtraInts::OfSet) + (static_cast<int>(DoorBase::doorSpriteSizeX) * i) + extraSpace, static_cast<int>(MenuOptions::GameStartY),
						true, aVectorOfRooms[aVectorOfDoors[i]->GetConnectingRoom(aCurrentRoom)]->GetRoomExplored(), aVectorOfRooms[aVectorOfDoors[i]->GetConnectingRoom(aCurrentRoom)]->GetRoomName());
					extraSpace += 3;
				}
				else
				{
					PrintDoorSprite(static_cast<int>(MenuOptions::GameStartX) + static_cast<int>(ExtraInts::OfSet) + (static_cast<int>(DoorBase::doorSpriteSizeX) * i) + extraSpace, static_cast<int>(MenuOptions::GameStartY),
						false, aVectorOfRooms[aVectorOfDoors[i]->GetConnectingRoom(aCurrentRoom)]->GetRoomExplored(), aVectorOfRooms[aVectorOfDoors[i]->GetConnectingRoom(aCurrentRoom)]->GetRoomName());
					extraSpace += 3;
				}
			}

			switch (ButtonPress())
			{
			case MenuOptions::MenuListLeft:
			{
				if (playerChoise > 0)
				{
					playerChoise--;
				}
				else
				{
					playerChoise = static_cast<int>(aVectorOfDoors.size()) - 1;
				}
				break;
			}
			case MenuOptions::MenuListRight:
			{
				if (playerChoise < static_cast<int>(aVectorOfDoors.size()) - 1)
				{
					playerChoise++;
				}
				else
				{
					playerChoise = 0;
				}
				break;
			}
			case MenuOptions::MenuListOption:
			{
				return playerChoise;
				break;
			}
			}
		}
	}

	void PrintDoorSprite(int aStartX, int aStartY, bool aTarget, bool aRoomExplored, std::string aRoomName)
	{
		if (aRoomExplored == false)
		{
			SetCursorPosition(aStartX, aStartY);
			std::cout << "     ______     ";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "  ,-' ;  ! `-.  ";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << " / :  !  :  . \\ ";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|_ ;   __:  ;  |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << ")| .  :)(.  !  |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|     (##)  _  |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|  :  ;`'  (_) (";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|  :  :  .     |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << ")_ !  ,  ;  ;  |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|| .  .  :  :  |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|  .  |  :  .  |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|___.------.___|";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "      ???       " << std::endl;
		}
		else if (aRoomExplored == true)
		{
			SetCursorPosition(aStartX, aStartY);
			std::cout << "     ______     ";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "  ,-'      `-.  ";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << " /            \\ ";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|              |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|              |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|              |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|              |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|              |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|              |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|              |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|              |";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "|______________|";
			SetCursorPosition(aStartX, ++aStartY);
			std::cout << "   " << aRoomName << std::endl;
		}

		if (aTarget)
		{
			SetCursorPosition(aStartX, aStartY += 2);
			SetColor(ColorInt::RedColorText);
			for (int j = 0; j < static_cast<int>(DoorBase::doorSpriteSizeX); j++)
			{
				if (j == 0 || j == static_cast<int>(DoorBase::doorSpriteSizeX) - 1)
				{
					std::cout << "-";
				}
				else
				{
					std::cout << "=";
				}
			}
			SetColor(ColorInt::WhiteColorText);
		}
		else
		{
			ClearArea(aStartX, aStartY += 2, static_cast<int>(DoorBase::doorSpriteSizeX));

		}
	}


	std::string ToString(ItemType aItem)
	{
		switch (aItem)
		{
		case ItemType::Dagger:
			return "Dagger";
			break;

		case ItemType::Sword:
			return "Sword";
			break;

		case ItemType::GreatSword:
			return "Great Sword";
			break;

		case ItemType::Helm:
			return "Helmet";
			break;

		case ItemType::Armor:
			return "Armor";
			break;

		default:
			return "No Item";
			break;
		}
	}
	std::string ToString(PrimeStats aPrimeStat)
	{
		switch (aPrimeStat)
		{
		case PrimeStats::Strength:
			return "Srenght";
			break;

		case PrimeStats::Dexterety:
			return "Dexterety";
			break;

		case PrimeStats::Charisma:
			return "Charisma";
			break;

		case PrimeStats::Armor:
			return "Armor";
			break;

		default:
			return "No Stat";
			break;
		}
	}
	std::string ToString(SecondaryStats aSecondaryStat)
	{
		switch (aSecondaryStat)
		{
		case SecondaryStats::Strength:
			return "Srenght";
			break;

		case SecondaryStats::Dexterety:
			return "Dexterety";
			break;

		case SecondaryStats::Charisma:
			return "Charisma";
			break;

		case SecondaryStats::MaxHp:
			return "Max Hp";
			break;

		case SecondaryStats::Damage:
			return "Damage";
			break;

		case SecondaryStats::Athletics:
			return "Athletics";
			break;

		case SecondaryStats::SlightOfHand:
			return "Slight of Hand";
			break;

		case SecondaryStats::Persuasion:
			return "Persuasion";
			break;

		case SecondaryStats::Armor:
			return "Armor";
			break;
		default:
			return "No Stat";
			break;
		}
	}

	void SetCursorVisibility(bool aSetCursor)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = aSetCursor;

		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

}
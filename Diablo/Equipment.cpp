#include "Equipment.h"
#include "Items.h"
#include <memory>

Equipment::Equipment()
{
	myEquipmentWeapon = nullptr;
	myEquipmentHelm = nullptr;
	myEquipmentArmor = nullptr;
}

void Equipment::SetEquipentWeapon(std::shared_ptr<Items> aItem)
{
	myEquipmentWeapon = aItem;
}

void Equipment::SetEquipentHelm(std::shared_ptr<Items> aItem)
{
	myEquipmentHelm = aItem;
}

void Equipment::SetEquipentArmor(std::shared_ptr<Items> aItem)
{
	myEquipmentArmor = aItem;
}

const std::shared_ptr<Items> Equipment::GetEquipmentWeapon() const
{
	return myEquipmentWeapon;
}

const std::shared_ptr<Items> Equipment::GetEquipmentHelm() const
{
	return myEquipmentHelm;
}

const std::shared_ptr<Items> Equipment::GetEquipmentArmor() const
{
	return myEquipmentArmor;
}
#pragma once
#include <memory>

class Items;

class Equipment
{
public:
	Equipment();
	void SetEquipentWeapon(std::shared_ptr<Items>);
	void SetEquipentHelm(std::shared_ptr<Items>);
	void SetEquipentArmor(std::shared_ptr<Items>);

	const std::shared_ptr<Items> GetEquipmentWeapon() const;
	const std::shared_ptr<Items> GetEquipmentHelm() const;
	const std::shared_ptr<Items> GetEquipmentArmor() const;


private:
	std::shared_ptr<Items> myEquipmentArmor;
	std::shared_ptr<Items> myEquipmentWeapon;
	std::shared_ptr<Items> myEquipmentHelm;

};


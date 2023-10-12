#include "EnemyFactory.h"
#include "Quick functions.h"

std::shared_ptr<Enemy> EnemyFactory::CreateEnemy(const eEnemyTyps aEnemyType) const
{
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(myEnemyTypes[static_cast<int>(aEnemyType)]);
	return enemy;
}

std::shared_ptr<Enemy> EnemyFactory::CreateEnemyWithRandomStats(const eEnemyTyps aEnemyType) const
{
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(myEnemyTypes[static_cast<int>(aEnemyType)]);

	enemy->SetHp(enemy->GetHp() + RandomNumber(0, 10));
	enemy->SetStrength(enemy->GetStrength() + RandomNumber(0, 5));
	enemy->SetDexterety(enemy->GetDexterety() + RandomNumber(0, 5));
	enemy->SetDodge(enemy->GetDodge() + RandomNumber(0, 5));
	return enemy;
}

void EnemyFactory::Init()
{
	myEnemyTypes[static_cast<int>(eEnemyTyps::Normal)].SetHp(45);
	myEnemyTypes[static_cast<int>(eEnemyTyps::Normal)].SetStrength(10);
	myEnemyTypes[static_cast<int>(eEnemyTyps::Normal)].SetDexterety(10);
	myEnemyTypes[static_cast<int>(eEnemyTyps::Normal)].SetDodge(5);

	myEnemyTypes[static_cast<int>(eEnemyTyps::Boss)].SetHp(120);
	myEnemyTypes[static_cast<int>(eEnemyTyps::Boss)].SetStrength(20);
	myEnemyTypes[static_cast<int>(eEnemyTyps::Boss)].SetDexterety(20);
	myEnemyTypes[static_cast<int>(eEnemyTyps::Boss)].SetDodge(5);
}




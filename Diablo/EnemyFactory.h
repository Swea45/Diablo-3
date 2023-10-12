#pragma once
#include <memory>
#include <array>
#include "Enums.h"
#include "Enemy.h"

class EnemyFactory
{
public:
	EnemyFactory() = default;
	~EnemyFactory() = default;

	void Init();

	std::shared_ptr<Enemy> CreateEnemy(const eEnemyTyps aEnemyType) const;
	std::shared_ptr<Enemy> CreateEnemyWithRandomStats(const eEnemyTyps aEnemyType) const;


private:
	std::array<Enemy, static_cast<int>(eEnemyTyps::count)> myEnemyTypes;
};


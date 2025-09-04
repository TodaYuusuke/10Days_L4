#pragma once
#include "../BaseEnemy.h"
#include <memory>
#include "NormalBossStateType.h"
#include "../state/IEnemyState.h"

class NormalBoss : public BaseEnemy{
public:
	NormalBoss();
	~NormalBoss() = default;

	void Initialize() override;
	void Update() override;

private:

};

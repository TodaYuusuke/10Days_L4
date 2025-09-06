#pragma once
#include "../BaseEnemy.h"
#include <memory>
#include "NormalBossStateType.h"
#include "../state/IEnemyState.h"

class NormalBoss : public BaseEnemy{
public:
	NormalBoss() = delete;
	NormalBoss(BaseEnemyData& data);
	~NormalBoss() = default;

	void Initialize(BaseEnemyData& data) override;
	void Update() override;

private:
	void SetData(BaseEnemyData& data) override;
	// データ
	NormalBossData& data_;

};

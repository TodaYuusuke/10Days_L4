#pragma once
#include "IEnemyState.h"
#include "../data/BaseEnemyData.h"
#include "../data/AttackDefaultData.h"

class NormalBossStateManager;

// 敵キャラクターのたたきつけ攻撃
class NormalEnemySlamState : public IEnemyState {
public:
	NormalEnemySlamState() = default;
	NormalEnemySlamState(const BaseEnemyData* data, NormalBossStateManager* sManager);
	~NormalEnemySlamState() = default;

	// 初期化処理
	void Enter(BaseEnemy* enemy) override;
	// 更新処理
	void Update(BaseEnemy* enemy) override;
	// 終了処理
	void Exit(BaseEnemy* enemy) override;

private:

	NormalBossStateManager* pStateManager_ = nullptr;
	const AttackDefaultData* pSlam_ = nullptr;

	// 時間
	float totalTime_ = 0.0f;
	float nowTime_ = 0.0f;
};

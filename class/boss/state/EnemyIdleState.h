#pragma once
#include "IEnemyState.h"
class NormalBossStateManager;

// 敵キャラクター移動stateクラス
class EnemyIdleState : public IEnemyState {
public:
	EnemyIdleState() = default;
	EnemyIdleState(const Vector2* idleTime, NormalBossStateManager* sManager);
	~EnemyIdleState() = default;

	// 初期化処理
	void Enter(BaseEnemy* enemy) override;
	// 更新処理
	void Update(BaseEnemy* enemy) override;
	// 終了処理
	void Exit(BaseEnemy* enemy) override;

private:

	const Vector2* pIdleTime_ = nullptr;
	NormalBossStateManager* pStateManager_ = nullptr;

	// 時間
	float idleTime_ = 0.0f;
	float nowTime_ = 0.0f;
};

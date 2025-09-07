#pragma once
#include "IEnemyState.h"

// 敵キャラクター移動stateクラス
class EnemyMoveState : public IEnemyState {
public:
	EnemyMoveState() = default;
	EnemyMoveState(const float* moveSpeed, NormalBossStateManager* sManager);
	~EnemyMoveState() = default;

	// 初期化処理
	void Enter(BaseEnemy* enemy) override;
	// 更新処理
	void Update(BaseEnemy* enemy) override;
	// 終了処理
	void Exit(BaseEnemy* enemy) override;

private:

	const float* pMoveSpeed_ = nullptr;
	NormalBossStateManager* pStateManager_ = nullptr;
	Vector2 velocity_ = { 0.0f,0.0f };

};

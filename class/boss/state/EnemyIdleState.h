#pragma once
#include "IEnemyState.h"


// 敵キャラクター移動stateクラス
class EnemyIdleState : public IEnemyState {
public:
	EnemyIdleState() = default;
	EnemyIdleState(const Vector2* idleTime);
	~EnemyIdleState() = default;

	// 初期化処理
	void Enter(BaseEnemy* enemy) override;
	// 更新処理
	void Update(BaseEnemy* enemy) override;
	// 終了処理
	void Exit(BaseEnemy* enemy) override;

	void Initialize(const Vector2* idleTime) {}

private:

	const Vector2* pIdleTime_ = nullptr;
};

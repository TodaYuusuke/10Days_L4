#include "EnemyMoveState.h"
#include "../normalBoss/NormalBossStateType.h"
#include "../normalBoss/NormalBossStateManager.h"
#include "../normalBoss/NormalBoss.h"

EnemyMoveState::EnemyMoveState(const float* moveSpeed, NormalBossStateManager* sManager) {
	pMoveSpeed_ = moveSpeed;
	pStateManager_ = sManager;
}

void EnemyMoveState::Enter(BaseEnemy* enemy) {
	velocity_ = pStateManager_->GetTargetPosition() - enemy->corePosition_;
	velocity_ = velocity_.Normalize();
}

void EnemyMoveState::Update(BaseEnemy* enemy) {
	Vector2 result = enemy->corePosition_;
	result += velocity_ * *pMoveSpeed_;
	Vector2 vec = pStateManager_->GetTargetPosition() - result;

	// 仮で距離が10未満だったらidleに切り替えるようにしている
	if (vec.Length() <= 10.0f) {
		pStateManager_->RequestStateChange();
		result = pStateManager_->GetTargetPosition();
	}
	enemy->corePosition_ = result;
}

void EnemyMoveState::Exit(BaseEnemy* enemy) {

}

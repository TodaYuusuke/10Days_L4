#include "EnemyMoveState.h"
#include "../normalBoss/NormalBossStateType.h"

EnemyMoveState::EnemyMoveState(const float* moveSpeed) {
	pMoveSpeed_ = moveSpeed;
}

void EnemyMoveState::Enter(BaseEnemy* enemy) {

}

void EnemyMoveState::Update(BaseEnemy* enemy) {

	enemy->RequestState(static_cast<uint8_t>(NormalBossStateType::Idel));
}

void EnemyMoveState::Exit(BaseEnemy* enemy) {

}

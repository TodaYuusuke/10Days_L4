#include "EnemyIdleState.h"
#include "../normalBoss/NormalBossStateType.h"

EnemyIdleState::EnemyIdleState(const Vector2* idleTime) {
	pIdleTime_ = idleTime;
}

void EnemyIdleState::Enter(BaseEnemy* enemy) {
	
}

void EnemyIdleState::Update(BaseEnemy* enemy) {
	enemy->RequestState(static_cast<uint8_t>(NormalBossStateType::Move));
}

void EnemyIdleState::Exit(BaseEnemy* enemy)
{
}

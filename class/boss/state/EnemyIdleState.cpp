#include "EnemyIdleState.h"
#include "../normalBoss/NormalBossStateType.h"

EnemyIdleState::EnemyIdleState(const Vector2* idleTime) {
	pIdleTime_ = idleTime;
}

void EnemyIdleState::Enter(BaseEnemy* enemy) {
	idleTime_ = LWP::Utility::Random::GenerateFloat(pIdleTime_->x, pIdleTime_->y);
	nowTime_ = 0.0f;
}

void EnemyIdleState::Update(BaseEnemy* enemy) {
	const float kDeltaTime = LWP::Info::GetDeltaTimeF();
	nowTime_ += kDeltaTime;
	
	// 待機時間が終わったらstateを変更
	if (idleTime_ < nowTime_) {
		enemy->RequestState(static_cast<uint8_t>(NormalBossStateType::Move));
	}

}

void EnemyIdleState::Exit(BaseEnemy* enemy) {

}

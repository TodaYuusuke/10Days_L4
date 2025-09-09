#include "EnemyIdleState.h"
#include "../normalBoss/NormalBossStateType.h"
#include "../normalBoss/NormalBossStateManager.h"

EnemyIdleState::EnemyIdleState(const Vector2* idleTime, NormalBossStateManager* sManager) {
	pIdleTime_ = idleTime;
	pStateManager_ = sManager;
}

void EnemyIdleState::Enter([[maybe_unused]] BaseEnemy* enemy) {
	idleTime_ = LWP::Utility::Random::GenerateFloat(pIdleTime_->x, pIdleTime_->y);
	nowTime_ = 0.0f;
}

void EnemyIdleState::Update(BaseEnemy* enemy) {
	const float kDeltaTime = LWP::Info::GetDeltaTimeF();
	nowTime_ += kDeltaTime;
	
	// 待機時間が終わったらstateを変更
	if (idleTime_ < nowTime_) {
		//*pTargetPos_ = Vector2(1280.0f, 0.0f);
		//enemy->RequestState(static_cast<uint8_t>(NormalBossStateType::Move));
		pStateManager_->RequestStateChange();
	}
}

void EnemyIdleState::Exit([[maybe_unused]] BaseEnemy* enemy) {

}

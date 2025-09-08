#include "NormalEnemySlamState.h"
#include "../normalBoss/NormalBossStateType.h"
#include "../normalBoss/NormalBossStateManager.h"

NormalEnemySlamState::NormalEnemySlamState(const BaseEnemyData* data, NormalBossStateManager* sManager) {
	const NormalBossData* d = dynamic_cast<const NormalBossData*>(data);
	pSlam_ = &d->slam;
}

void NormalEnemySlamState::Enter([[maybe_unused]] BaseEnemy* enemy) {
	totalTime_ = pSlam_->startupLag + pSlam_->damageTime + pSlam_->endingLag;
	nowTime_ = 0.0f;
}

void NormalEnemySlamState::Update(BaseEnemy* enemy) {
	// 時間の加算
	const float kDeltaTime = LWP::Info::GetDeltaTimeF();
	nowTime_ += kDeltaTime;

	Vector2 result = enemy->corePosition_;
	// 攻撃の一連の動作がおわったらstateを変更
	if (totalTime_ < nowTime_) {
		pStateManager_->RequestStateChange();
	}
	
	enemy->corePosition_ = result;
}

void NormalEnemySlamState::Exit([[maybe_unused]] BaseEnemy* enemy) {

}

#include "EnemyIdleState.h"
#include "../normalBoss/NormalBossStateType.h"
#include "../normalBoss/NormalBossStateManager.h"
#include "../../minion/MinionManager.h"


EnemyIdleState::EnemyIdleState(const Vector2* idleTime, NormalBossStateManager* sManager, MinionManager* mManager) {
	pIdleTime_ = idleTime;
	pStateManager_ = sManager;
	pMinionManager_ = mManager;
}

void EnemyIdleState::Enter([[maybe_unused]] BaseEnemy* enemy) {
	idleTime_ = LWP::Utility::Random::GenerateFloat(pIdleTime_->x, pIdleTime_->y);
	nowTime_ = 0.0f;
	isPushMinion_ = true;
}

void EnemyIdleState::Update(BaseEnemy* enemy) {
	const float kDeltaTime = LWP::Info::GetDeltaTimeF();
	nowTime_ += kDeltaTime;
	
	// minionの流れ
	if (isPushMinion_) {
		auto& handle = pMinionManager_->GetMinions();
		for (auto& minion : handle) {
			// Absorbタイプだったら
			if (minion.GetCurrentStateType() == MinionStateType::Absorb) {
				// 座標を指定してFormにリクエストする
				minion.SetRequestStateType(MinionStateType::Foam);
				minion.SetPosition(enemy->corePosition_);
				isPushMinion_ = false;
				break;
			}
		}
	}

	// 待機時間が終わったらstateを変更
	if (idleTime_ < nowTime_) {
		pStateManager_->RequestStateChange();
	}
}

void EnemyIdleState::Exit([[maybe_unused]] BaseEnemy* enemy) {

}

#include "NormalEnemySlamState.h"
#include "../normalBoss/NormalBossStateType.h"
#include "../normalBoss/NormalBossStateManager.h"
#include "../data/NormalBossData.h"
#include "../normalBoss/NormalBoss.h"
#include "../../areaOffEffect/AreaOffEffectManager.h"
#include "../../ColMaskGetter.h"

NormalEnemySlamState::NormalEnemySlamState(const BaseEnemyData* data, NormalBossStateManager* sManager) {
	const NormalBossData* d = dynamic_cast<const NormalBossData*>(data);
	pSlam_ = &d->slam;
	pStateManager_ = sManager;

	// マスクの作成
	coll2D_.mask.SetBelongFrag(ColMaskGetter::GetEnemyAttack());
	coll2D_.mask.SetHitFrag(ColMaskGetter::GetPlayer() | ColMaskGetter::GetWall());
	coll2D_.isActive = false;
}

void NormalEnemySlamState::Enter([[maybe_unused]] BaseEnemy* enemy) {
	totalTime_ = pSlam_->startupLag + pSlam_->damageTime + pSlam_->endingLag;
	nowTime_ = 0.0f;
	AreaOffEffectManager::RequestCreate(enemy->corePosition_, pSlam_->attackRange.x, *pSlam_);
	enemy->SetAttackPower(pSlam_->attackPower);

	// 当たり判定の設定
	coll2D_.worldTF.translation = { enemy->corePosition_.x, enemy->corePosition_.y, 0.0f };
	coll2D_.isActive = false;
	
	LWP::Object::Collider2D::Circle& circle = coll2D_.SetBroadShape<LWP::Object::Collider2D::Circle>();
	circle.radius = pSlam_->attackRange.x;
}

void NormalEnemySlamState::Update(BaseEnemy* enemy) {
	// 時間の加算
	const float kDeltaTime = LWP::Info::GetDeltaTimeF();
	nowTime_ += kDeltaTime;
	Vector2 result = enemy->corePosition_;
	// ダメージが入る時間ならば
	if (pSlam_->startupLag < nowTime_ && nowTime_ < pSlam_->startupLag + pSlam_->damageTime) {
		// 当たり判定を有効可
		coll2D_.isActive = true;
	}
	else { coll2D_.isActive = false; }
	// 攻撃の一連の動作がおわったらstateを変更
	if (totalTime_ < nowTime_) {
		pStateManager_->RequestStateChange();
	}
	
	enemy->corePosition_ = result;
}

void NormalEnemySlamState::Exit([[maybe_unused]] BaseEnemy* enemy) {
	coll2D_.isActive = false;
}

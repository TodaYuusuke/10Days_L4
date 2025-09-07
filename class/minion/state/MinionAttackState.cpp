#include "MinionAttackState.h"
#include <Adapter.h>
#include "../Minion.h"
#include "../MinionManager.h"
#include "../MinionGlobalData.h"
using namespace LWP::Math;
using namespace LWP::Info;

MinionAttackState::MinionAttackState()
	:	motivationTime_(0.0f),
		attackCoolTime_(0.0f)
{
}

void MinionAttackState::Enter(Minion* minion)
{

	attackCoolTime_ = MinionGlobalData::GetAttackCoolTimeMax();

}

void MinionAttackState::Update(Minion* minion)
{

	// 向き

	// ボスの位置
	const Vector2 kBossPosition = {0.0f,0.0f};
	// 自分の位置
	const Vector2 kMyPosition = minion->GetPosition();
	// 向き
	const Vector2 kDirection = (kBossPosition - kMyPosition).Normalize();
	minion->SetDirection(kDirection);

	const float kDeltaTime = static_cast<float>(GetDeltaTime());

	motivationTime_ -= kDeltaTime;

	// 攻撃速度
	float attackSpeed = kDeltaTime;

	// やる気あり
	if (motivationTime_ > 0.0f) {
		motivationTime_ -= kDeltaTime;
		attackSpeed *= MinionGlobalData::GetMotivationMultiplier();
	}
	// やる気なし
	else {
		motivationTime_ = 0.0f;
	}

	// 石投げ処理
	attackCoolTime_ -= attackSpeed;
	if (attackCoolTime_ <= 0.0f) {
		// 攻撃
		minion->ThrowStone();
		attackCoolTime_ = MinionGlobalData::GetAttackCoolTimeMax();
	}

}

void MinionAttackState::Exit(Minion* minion)
{
}

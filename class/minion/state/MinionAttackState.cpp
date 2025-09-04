#include "MinionAttackState.h"
#include <Adapter.h>
#include "../Minion.h"
#include "../MinionManager.h"

using namespace LWP::Info;

MinionAttackState::MinionAttackState()
	:	motivationTime_(0.0f),
		attackCoolTime_(0.0f)
{
}

void MinionAttackState::Enter(Minion* minion)
{

	const float kEnterAttackCoolTime = 1.0f;
	attackCoolTime_ = kEnterAttackCoolTime;

}

void MinionAttackState::Update(Minion* minion)
{

	const float kDeltaTime = static_cast<float>(GetDeltaTime());

	motivationTime_ -= kDeltaTime;

	// 攻撃速度
	float attackSpeed = kDeltaTime;

	// やる気あり
	if (motivationTime_ > 0.0f) {
		motivationTime_ -= kDeltaTime;
		const float kMotivationMultiplier = 1.5f;
		attackSpeed *= kMotivationMultiplier;
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
		const float kAttackCoolTimeMax = 2.0f;
		attackCoolTime_ = kAttackCoolTimeMax;
	}

}

void MinionAttackState::Exit(Minion* minion)
{
}

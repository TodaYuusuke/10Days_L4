#include "MinionAttackState.h"
#include <Adapter.h>

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

	motivationTime_ -= GetDeltaTime();

	// UŒ‚‘¬“x
	float attackSpeed = GetDeltaTime();

	// ‚â‚é‹C‚ ‚è
	if (motivationTime_ > 0.0f) {
		motivationTime_ -= GetDeltaTime();
		const float kMotivationMultiplier = 1.5f;
		attackSpeed *= kMotivationMultiplier;
	}
	// ‚â‚é‹C‚È‚µ
	else {
		motivationTime_ = 0.0f;
	}

	// Î“Š‚°ˆ—
	attackCoolTime_ -= attackSpeed;
	if (attackCoolTime_ <= 0.0f) {
		// UŒ‚

		const float kAttackCoolTimeMax = 2.0f;
		attackCoolTime_ = kAttackCoolTimeMax;

	}

}

void MinionAttackState::Exit(Minion* minion)
{
}

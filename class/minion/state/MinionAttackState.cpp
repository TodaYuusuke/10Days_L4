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

	// 切り替えるか
	const Vector2 kMinionPosition = minion->GetPosition();
	const Vector2 kMeetingPlacePosition = minion->GetMinionManager()->GetMeetingPlace()->GetPosition();
	Vector2 dir = (kMeetingPlacePosition - kMinionPosition);
	if (dir.Length() > MinionGlobalData::GetMoveStateChangesDistance()) {
		minion->SetRequestStateType(MinionStateType::Move);
	}

}

void MinionAttackState::Exit(Minion* minion)
{
}

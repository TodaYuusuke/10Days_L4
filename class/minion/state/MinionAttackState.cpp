#include "MinionAttackState.h"
#include <Adapter.h>
#include "../Minion.h"
#include "../MinionManager.h"
#include "../MinionGlobalData.h"
using namespace LWP::Math;
using namespace LWP::Info;

MinionAttackState::MinionAttackState()
	:	attackCoolTime_(0.0f)
{
}

void MinionAttackState::Enter(Minion* minion)
{

	minion;
	attackCoolTime_ = MinionGlobalData::GetAttackCoolTimeMax();

}

void MinionAttackState::Update(Minion* minion)
{

	// 向き

	// ボスの位置
	const Vector2 kBossPosition = minion->GetMinionManager()->GetEnemyManager()->GetEnemyPosition();
	// 自分の位置
	const Vector2 kMyPosition = minion->GetPosition();
	// 向き
	const Vector2 kDirection = (kBossPosition - kMyPosition).Normalize();
	minion->SetDirection(kDirection);

	const float kDeltaTime = static_cast<float>(GetDeltaTime());

	float motivationTime = minion->GetMotivationTime();

	motivationTime -= kDeltaTime;

	// 攻撃速度
	float attackSpeed = kDeltaTime;

	// やる気あり
	if (motivationTime > 0.0f) {
		motivationTime -= kDeltaTime;
		//attackSpeed *= MinionGlobalData::GetMotivationMultiplier();
	}
	// やる気なし
	else {
		motivationTime = 0.0f;
		// Idleへ
		minion->SetRequestStateType(MinionStateType::Idle);
	}

	// やる気の値をセット
	minion->SetMotivationTime(motivationTime);

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
	minion;
}

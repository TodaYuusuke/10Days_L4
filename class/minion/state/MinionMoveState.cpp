#include "MinionMoveState.h"
#include "../Minion.h"
#include "../MinionManager.h"

#include <numbers>

using namespace LWP::Math;

MinionMoveState::MinionMoveState()
	: speed_(0.5f)
{
}

void MinionMoveState::Enter(Minion* minion)
{
}

void MinionMoveState::Update(Minion* minion)
{

	// 移動する
	const Vector2 kMinionPosition = minion->GetPositon();
	const Vector2 kMeetingPlacePosition = minion->GetMinionManager()->GetMeetingPlace()->GetPosition();

	// 番号から最終移動地点を変更
	const int  kSerialNumber = minion->GetSerialNumber();
	const float kDegreeInterval = 360.0f / minion->GetMinionManager()->kMinionNumMax_;
	const float kTheta = std::numbers::pi / 180.0f * kSerialNumber * kDegreeInterval;
	const float kRadius = 100.0f;
	const Vector2 kAddPosition = { std::cosf(kTheta) * kRadius, std::sinf(kTheta) * kRadius };

	const Vector2 kTargetPosition = kMeetingPlacePosition + kAddPosition;

	// 移動方向
	Vector2 dir = (kTargetPosition - kMinionPosition);
	if (dir.Length() == 0.0f) {
		return;
	}
	dir = dir.Normalize();
	// 移動
	const Vector2 kNewMinionPosition = kMinionPosition + (dir * speed_);
	minion->SetPositon(kNewMinionPosition);
	// 回転、方向
	minion->SetDirection(dir);

}

void MinionMoveState::Exit(Minion* minion)
{
}

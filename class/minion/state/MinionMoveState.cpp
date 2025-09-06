#include "MinionMoveState.h"
#include "../Minion.h"
#include "../MinionManager.h"

#include <numbers>
#include "../MinionGlobalData.h"

using namespace LWP::Math;
using namespace LWP::Utility;

void MinionMoveState::Enter(Minion* minion)
{
	addRotate_ = 0.0f;
}

void MinionMoveState::Update(Minion* minion)
{

	// 移動する
	const Vector2 kMinionPosition = minion->GetPosition();
	const Vector2 kMeetingPlacePosition = minion->GetMinionManager()->GetMeetingPlace()->GetPosition();

	// 番号から最終移動地点を変更
	const int  kSerialNumber = minion->GetSerialNumber();

	float degreeInterval = 0.0f;
	float theta = 0.0f;
	float radius = 0.0f;
	
	int k = 1; // 円
	int n = 4; // その縁の人数制限
	int serialNumberOffset = 1;

	if (kSerialNumber == 0) {
		radius = 0.0f;
	}
	else {
		while (kSerialNumber > n + serialNumberOffset - 1) {

			serialNumberOffset += n;
			n *= 2;
			++k;
		}

		degreeInterval = 360.0f / n;
		theta = static_cast<float>(std::numbers::pi) / 180.0f * (kSerialNumber - serialNumberOffset) * degreeInterval;
		radius = k * 30.0f;
	}
	
	const Vector2 kAddPosition = { std::cosf(theta) * radius, std::sinf(theta) * radius };
	const Vector2 kTargetPosition = kMeetingPlacePosition + kAddPosition;

	// 移動方向
	Vector2 dir = (kTargetPosition - kMinionPosition);
	if (dir.Length() <= MinionGlobalData::GetAttackStateChangesDistance()) {
		minion->SetRequestStateType(MinionStateType::Attack);
		return;
	}
	dir = dir.Normalize();

	// 回転させて不規則に動くように
	const float kSddRotateFluctuation = MinionGlobalData::GetAddRotateFluctuation();
	addRotate_ += Random::GenerateFloat(-kSddRotateFluctuation, kSddRotateFluctuation);
	const float kSddRotateMax = MinionGlobalData::GetAddRotateMax();
	addRotate_ = std::clamp(addRotate_, -kSddRotateMax, kSddRotateMax);
	Matrix4x4 randomRotateMatrix = Matrix4x4::CreateRotateZMatrix(addRotate_);
	dir = dir * randomRotateMatrix;
	// 移動
	const Vector2 kNewMinionPosition = kMinionPosition + (dir * MinionGlobalData::GetSpeed());
	minion->SetPosition(kNewMinionPosition);
	// 回転、方向
	minion->SetDirection(dir);

}

void MinionMoveState::Exit(Minion* minion)
{
}

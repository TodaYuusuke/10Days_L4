#include "MinionMoveState.h"
#include "../Minion.h"
#include "../MinionManager.h"

#include <numbers>
#include "../MinionGlobalData.h"

using namespace LWP::Math;
using namespace LWP::Utility;

MinionMoveState::MinionMoveState()
	:	addRotate_(0.0f),
		speed_(0.0f)
{
}

void MinionMoveState::Enter(Minion* minion)
{
	minion;
	addRotate_ = 0.0f;
	const float kAddSpeedFluctuation = MinionGlobalData::GetAddSpeedFluctuation();
	speed_ = MinionGlobalData::GetSpeed() + Random::GenerateFloat(-kAddSpeedFluctuation, kAddSpeedFluctuation);
}

void MinionMoveState::Update(Minion* minion)
{


	MinionManager* minionManager = minion->GetMinionManager();

	// 画面端処理用画像の半分の値
	const Vector2 kTextureHalfSize =
	{ MinionGlobalData::GetTextureSize().x * MinionGlobalData::GetSpriteScale().x * 0.5f,
		MinionGlobalData::GetTextureSize().y * MinionGlobalData::GetSpriteScale().y * 0.5f };

	// 移動する
	const Vector2 kMinionPosition = minion->GetPosition();
	const Vector2 kTargetPosition = minionManager->GetTargetPosition();

	// 移動方向
	Vector2 sub = (kTargetPosition - kMinionPosition);
	Vector2 dir = sub.Normalize();

	// 回転させて不規則に動くように
	const float kSddRotateFluctuation = MinionGlobalData::GetAddRotateFluctuation();
	addRotate_ += Random::GenerateFloat(-kSddRotateFluctuation, kSddRotateFluctuation);
	const float kSddRotateMax = MinionGlobalData::GetAddRotateMax();
	addRotate_ = std::clamp(addRotate_, -kSddRotateMax, kSddRotateMax);
	Matrix4x4 randomRotateMatrix = Matrix4x4::CreateRotateZMatrix(addRotate_);
	dir = dir * randomRotateMatrix;
	// 移動
	Vector2 newMinionPosition = kMinionPosition + (dir * speed_);

	// 画面端処理
	newMinionPosition.x = std::clamp(newMinionPosition.x, kTextureHalfSize.x, 1920.0f - kTextureHalfSize.x);
	newMinionPosition.y = std::clamp(newMinionPosition.y, kTextureHalfSize.y, 1080.0f - kTextureHalfSize.y);

	// 移動
	minion->SetPosition(newMinionPosition);

	// 回転、方向
	minion->SetDirection(dir);

	// リクエスト
	//倍率
	const float kDistanceMagnification = static_cast<float>(minionManager->GetAttackMinionNum()) / static_cast<float>(minionManager->kMinionNumMax_);
	// リクエスト決定
	if (sub.Length() <= (MinionGlobalData::GetIdleStateChangesDistance() * Easing::CallFunction(Easing::Type::OutExpo, kDistanceMagnification)) + MinionGlobalData::GetRequestCheckAddLength()) {
		minion->SetRequestStateType(MinionStateType::Idle);
	}

}

void MinionMoveState::Exit(Minion* minion)
{
	minion;
}

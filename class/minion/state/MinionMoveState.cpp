#include "MinionMoveState.h"
#include "../Minion.h"
#include "../MinionManager.h"

#include <numbers>
#include "../MinionGlobalData.h"

using namespace LWP::Math;
using namespace LWP::Utility;

MinionMoveState::MinionMoveState()
	: addRotate_(0.0f)
{
}

void MinionMoveState::Enter(Minion* minion)
{
	addRotate_ = 0.0f;
}

void MinionMoveState::Update(Minion* minion)
{

	// 画面端処理用画像の半分の値
	const Vector2 kTextureHalfSize =
	{ MinionGlobalData::GetTextureSize().x * MinionGlobalData::GetSpriteScale().x * 0.5f,
		MinionGlobalData::GetTextureSize().y * MinionGlobalData::GetSpriteScale().y * 0.5f };

	// 移動する
	const Vector2 kMinionPosition = minion->GetPosition();
	const Vector2 kTargetPosition = minion->GetMinionManager()->GetTargetPosition();

	// 移動方向
	Vector2 dir = (kTargetPosition - kMinionPosition);
	dir = dir.Normalize();

	// 回転させて不規則に動くように
	const float kSddRotateFluctuation = MinionGlobalData::GetAddRotateFluctuation();
	addRotate_ += Random::GenerateFloat(-kSddRotateFluctuation, kSddRotateFluctuation);
	const float kSddRotateMax = MinionGlobalData::GetAddRotateMax();
	addRotate_ = std::clamp(addRotate_, -kSddRotateMax, kSddRotateMax);
	Matrix4x4 randomRotateMatrix = Matrix4x4::CreateRotateZMatrix(addRotate_);
	dir = dir * randomRotateMatrix;
	// 移動
	Vector2 newMinionPosition = kMinionPosition + (dir * MinionGlobalData::GetSpeed());

	// 画面端処理
	newMinionPosition.x = std::clamp(newMinionPosition.x, kTextureHalfSize.x, 1920.0f - kTextureHalfSize.x);
	newMinionPosition.y = std::clamp(newMinionPosition.y, kTextureHalfSize.y, 1080.0f - kTextureHalfSize.y);

	// 移動
	minion->SetPosition(newMinionPosition);

	// 回転、方向
	minion->SetDirection(dir);

}

void MinionMoveState::Exit(Minion* minion)
{
}

#include "TitleMinion.h"
#include "../minion/MinionGlobalData.h"
using namespace LWP::Math;
using namespace LWP::Info;

TitleMinion::TitleMinion()
	:	spriteSystem_(nullptr),
		position_({ 960.0f, 800.0f }),
		direction_({1.0f,0.0f }),
		stone_(nullptr),
		motivationTime_(0.0f),
		attackCoolTime_(0.0f)
{
	Initialize();
}

TitleMinion::~TitleMinion()
{
}

void TitleMinion::Initialize()
{
	spriteSystem_ = std::make_unique<MinionSpriteSystem>();
	stone_ = std::make_unique<Stone>();
}

void TitleMinion::Update()
{
	
	spriteSystem_->Update(MinionStateType::Attack, position_, direction_);

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
		stone_->Reset(position_, direction_);
		attackCoolTime_ = MinionGlobalData::GetAttackCoolTimeMax();
	}
	
	stone_->Update();

}

void TitleMinion::DebugGUI()
{
}


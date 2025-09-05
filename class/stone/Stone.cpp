#include "Stone.h"
#include "StoneGlobalData.h"
using namespace LWP::Math;

Stone::Stone()
	:	position_({0.0f,0.0f}),
		direction_({ 0.0f,0.0f }),
		speed_(0.0f),
		sprite_(),
		isDead_(false)
{
	Initialize();
}

Stone::Stone(const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction)
	:	position_(position),
		direction_(direction),
		speed_(0.0f),
		sprite_(),
		isDead_(false)
{
	Initialize();
}

Stone::~Stone()
{
}

void Stone::Initialize()
{

	// 初速度
	speed_ = StoneGlobalData::GetInitialSpeed();

	// スプライト
	sprite_.LoadTexture("Stone.png");
	sprite_.worldTF.scale = StoneGlobalData::GetSpriteScale();

}

void Stone::Update()
{

	// 速度計算
	speed_ += StoneGlobalData::GetAcceleration();
	if (speed_ <= 0.0f || speed_ > StoneGlobalData::GetInitialSpeed()) {
		speed_ = 0.0f;
		isDead_ = true;
	}
	// 速度
	const Vector2 velocity = speed_ * direction_;
	// 移動処理
	position_ += velocity;

	// 位置の移動
	sprite_.worldTF.translation = { position_.x, position_.y, StoneGlobalData::GetPositionZ()};
	// 回転
	const Vector3 kDir3D = { direction_.x, direction_.y, 0.0f };
	sprite_.worldTF.rotation = Quaternion::ConvertFromTo(Vector3{ 0.0f,1.0f,0.0f }, kDir3D);

}

#include "Stone.h"
#include "StoneGlobalData.h"
#include "../ColMaskGetter.h"
using namespace LWP::Math;
using namespace LWP::Object;
using namespace LWP::Utility;

Stone::Stone()
	:	position_({0.0f,0.0f}),
		direction_({ 0.0f,0.0f }),
		speed_(0.0f),
		sprite_(),
		isDead_(false),
		collider_()
{
	Initialize();
}

Stone::Stone(const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction)
	:	position_(position),
		direction_(direction),
		speed_(0.0f),
		sprite_(),
		isDead_(false),
		collider_()
{
	Initialize();
}

Stone::~Stone()
{
}

void Stone::Initialize()
{

	// 初速度
	speed_ = StoneGlobalData::GetInitialSpeed() + Random::GenerateFloat(0.0f, 0.5f);;

	// スプライト
	sprite_.LoadTexture("Stone.png");
	sprite_.worldTF.scale = StoneGlobalData::GetSpriteScale();
	
	// サークル
	Collider2D::Circle& circle = collider_.SetBroadShape<Collider2D::Circle>();
	circle.radius = StoneGlobalData::GetColliderRadius();
	// 親子
	collider_.worldTF.Parent(&sprite_.worldTF);

	// 関数
	// ヒットした瞬間のとき
	collider_.enterLambda = [this](Collision2D* hitTarget) {
		hitTarget;
		isDead_ = true;
		sprite_.isActive = false;
		};

	// マスク、所属
	collider_.mask.SetBelongFrag(ColMaskGetter::GetBullet() + ColMaskGetter::GetPlayer());
	// マスク,hit
	collider_.mask.SetHitFrag(ColMaskGetter::GetEnemy());


}

void Stone::Update()
{

	// 速度計算
	speed_ += StoneGlobalData::GetAcceleration();
	if (speed_ <= 0.0f || speed_ > StoneGlobalData::GetInitialSpeed()) {
		speed_ = 0.0f;
		isDead_ = true;
		sprite_.isActive = false;
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
	// 大きさ
	const float kScale = (1.0f - 4.0f * std::powf(speed_ / StoneGlobalData::GetInitialSpeed() - 0.5f, 2.0f)) * 0.3f;
	sprite_.worldTF.scale = { StoneGlobalData::GetSpriteScale().x + kScale, StoneGlobalData::GetSpriteScale().y + kScale,1.0f };

}

void Stone::Reset(const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction)
{

	// 初速度
	speed_ = StoneGlobalData::GetInitialSpeed();

	position_ = position;
	direction_ = direction;

	sprite_.isActive = true;

}

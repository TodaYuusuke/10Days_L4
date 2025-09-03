#include "Wall.h"
using namespace LWP::Math;

// スプライトの大きさ
const Vector2 Wall::kSpriteSize_ = { 100.0f, 100.0f };

Wall::Wall()
	:	start_({0.0f,0.0f}),
		end_({ 0.0f,0.0f }),
		hp_(0),
		lifeTime_(0.0f),
		sprite_(),
		isDead_(false)
{
}

Wall::Wall(const LWP::Math::Vector2& start, const LWP::Math::Vector2 end, float hp, float lifeTime)
	:	start_(start),
		end_(end),
		hp_(hp),
		lifeTime_(lifeTime),
		sprite_(),
		isDead_(false)
{

	Initilaize();

}

Wall::~Wall()
{
}

void Wall::Initilaize()
{

	sprite_.LoadTexture("Wall.png");

	// 位置
	const Vector2 spritePosition = (end_ + start_) / 2.0f;
	// Z座標（描画順）
	const float kPositionZ = 0.0f;
	sprite_.worldTF.translation = { spritePosition.x, spritePosition.y, kPositionZ };
	// 回転
	const Vector2 kDir2D = (end_ - start_).Normalize();
	const Vector3 kDir3D = { kDir2D.x, kDir2D.y, 0.0f };
	sprite_.worldTF.rotation = Quaternion::ConvertFromTo(Vector3{ 0.0f,1.0f,0.0f }, kDir3D);
	// 大きさ
	const float kLength = (end_ - start_).Length();
	sprite_.worldTF.scale.y = (kLength / kSpriteSize_.y) + 0.1f;

}

void Wall::Update()
{

	//生存時間
	lifeTime_ -= LWP::Info::GetDeltaTime();

	if (lifeTime_ <= 0.0f) {
		isDead_ = true;
	}

}

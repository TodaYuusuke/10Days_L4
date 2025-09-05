#include "Wall.h"
#include "../PlayerGlobalData.h"
using namespace LWP::Math;

Wall::Wall()
	:	start_({0.0f,0.0f}),
		end_({ 0.0f,0.0f }),
		hp_(0),
		lifeTime_(0.0f),
		sprite_(),
		isDead_(false)
{
}

Wall::Wall(const LWP::Math::Vector2& start, const LWP::Math::Vector2 end, int hp, float lifeTime)
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
	sprite_.worldTF.scale.x = PlayerGlobalData::GetWallSpriteScale().x;

	// 位置
	const Vector2 spritePosition = (end_ + start_) / 2.0f;
	sprite_.worldTF.translation = { spritePosition.x, spritePosition.y, PlayerGlobalData::GetWallPositionZ()};
	// 回転
	const Vector2 kDir2D = (end_ - start_).Normalize();
	const Vector3 kDir3D = { kDir2D.x, kDir2D.y, 0.0f };
	sprite_.worldTF.rotation = Quaternion::ConvertFromTo(Vector3{ 0.0f,1.0f,0.0f }, kDir3D);
	// 大きさ
	const float kLength = (end_ - start_).Length();
	sprite_.worldTF.scale.y = (kLength / PlayerGlobalData::GetWallTextureSize().y) + +PlayerGlobalData::GetWallSpriteScale().x;;

}

void Wall::Update()
{

	//生存時間
	lifeTime_ -= static_cast<float>(LWP::Info::GetDeltaTime());

	if (lifeTime_ <= 0.0f) {
		isDead_ = true;
	}

}

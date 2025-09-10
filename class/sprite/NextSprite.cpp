#include "NextSprite.h"
#include <numbers>
using namespace LWP::Info;

NextSprite::NextSprite()
	:	sprite_(),
		basePosition_(),
		addValue_()
{
}

NextSprite::~NextSprite()
{
}

void NextSprite::Initialize()
{

	sprite_.LoadTexture("Enwokake.png");

	basePosition_ = {1920.0f / 2.0f, 850.0f};

}

void NextSprite::Update()
{

	addValue_ = std::fmodf(addValue_ + static_cast<float>(GetDeltaTime()), (2.0f * static_cast<float>(std::numbers::pi)));

	const float kMaxY = 50.0f;

	sprite_.worldTF.translation =
	{ basePosition_.x,
		basePosition_.y + std::sinf(addValue_) * kMaxY,
		-50.0f
	};

}

void NextSprite::SetIsActive(bool isActive)
{

	sprite_.isActive = isActive;

}

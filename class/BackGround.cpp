#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Initialize()
{

	sprite_.LoadTexture("backGround.png");
	sprite_.worldTF.scale.x = 1920.0f / 256.0f;
	sprite_.worldTF.scale.y = 1080.0f / 256.0f;

	sprite_.worldTF.translation.x = 1920.0f * 0.5f;
	sprite_.worldTF.translation.y = 1080.0f * 0.5f;
	sprite_.worldTF.translation.z = 1000.0f;

}

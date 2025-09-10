#include "GameSprite.h"

GameSprite::GameSprite()
{
}

GameSprite::~GameSprite()
{
}

void GameSprite::Initialize()
{

	sprite_.LoadTexture("Game.png");

	sprite_.SetSplitSize({ 512.0f,128.0f });
	sprite_.worldTF.translation = { 1920.0f / 2.0f, 540.0f, 50.0f };
	sprite_.worldTF.scale = { 3.0f,3.0f };

}

void GameSprite::Update()
{
}

void GameSprite::SetIsActive(bool isActive)
{

	sprite_.isActive = isActive;

}

bool GameSprite::GetIsActive()
{

	return sprite_.isActive;

}

void GameSprite::SetIndex(int index)
{
	sprite_.index = index;
}

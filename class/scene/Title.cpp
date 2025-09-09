#include "Title.h"

// 初期化
void Title::Initialize() {

	drawing_ = std::make_unique<Drawing>();
	playerMouseOperation_ = std::make_unique<PlayerMouseOperation>();
	minion_ = std::make_unique<TitleMinion>();

	titleSprite_.LoadTexture("Title.png");
	titleSprite_.worldTF.translation = { 1920.0f / 2.0f, 1080.0f / 2.0f, 0.0f };

}

// 更新
void Title::Update() {


	playerMouseOperation_->Update();

	drawing_->Update(playerMouseOperation_->GetIsDragging());

	minion_->Update();

}
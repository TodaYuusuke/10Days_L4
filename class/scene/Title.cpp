#include "Title.h"
#include "TestScene.h"

using namespace LWP;
using namespace LWP::Input;

// 初期化
void Title::Initialize() {

	drawing_.Initialize();
	playerMouseOperation_.Initialize();
	minion_.Initialize();

	titleSprite_.LoadTexture("Title.png");
	titleSprite_.worldTF.translation = { 1920.0f / 2.0f, 1080.0f / 2.0f, 0.0f };

	sceneTransitionBlackOut_.Initialize();
	sceneTransitionBlackOut_.SetIsFadeIn(false);

	backGround_.Initialize();

}

// 更新
void Title::Update() {

	if (!sceneTransitionBlackOut_.GetStoppingUpdates()) {
		sceneTransitionBlackOut_.Update();
		if (sceneTransitionBlackOut_.GetSwitchScene()) {
			nextSceneFunction = []() { return new TestScene(); };
		}
	}
	else {
		if (drawing_.GetGameStart()) {
			sceneTransitionBlackOut_.Reset();	// 次のシーンに行くための処理
		}
	}

	playerMouseOperation_.Update();

	drawing_.Update(playerMouseOperation_.GetIsDragging());

	minion_.Update();

}
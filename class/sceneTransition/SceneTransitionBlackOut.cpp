#include "SceneTransitionBlackOut.h"

using namespace LWP::Info;

SceneTransitionBlackOut::SceneTransitionBlackOut()
	:	fadeInTime_(),
		fadeOutTime_(),
		fadeTimer_(),
		transitioning_(),
		isFadeIn_(),
		switchScene_(),
		stoppingUpdates_(),
		sprite_()
{
}

SceneTransitionBlackOut::~SceneTransitionBlackOut()
{
}

void SceneTransitionBlackOut::Initialize()
{

	Reset();

	sprite_.material.color.R = 0;
	sprite_.material.color.G = 0;
	sprite_.material.color.B = 0;

	sprite_.worldTF.translation = { 1920.0f * 0.5f, 1080.0f * 0.5f, -100.0f };
	sprite_.worldTF.scale = { 20.0f, 11.0f, 1.0f };

}

void SceneTransitionBlackOut::Update()
{

	if (stoppingUpdates_) {
		return;
	}

	fadeTimer_ += static_cast<float>(GetDeltaTime());

	if (isFadeIn_) {
		if (fadeTimer_ >= fadeInTime_) {
			fadeTimer_ = 0.0f;
			isFadeIn_ = false;
			switchScene_ = true;
		}
	}
	else {
		if (fadeTimer_ >= fadeOutTime_) {
			transitioning_ = false;
			stoppingUpdates_ = true;
			sprite_.material.color.A = 0;
			return;
		}
	}

	// α値変更
	float alpha = 0.0f;
	if (isFadeIn_) {
		alpha = fadeTimer_ / fadeInTime_;
	}
	else {
		alpha = 1.0f - fadeTimer_ / fadeOutTime_;
	}

	sprite_.material.color.A = static_cast<unsigned char>(alpha * 255.0f);

}

void SceneTransitionBlackOut::Reset()
{
	fadeInTime_ = 1.0f; //フェードインタイム
	fadeOutTime_ = 1.0f; //フェードアウトタイム
	fadeTimer_ = 0.0f; // タイマー

	transitioning_ = true; //遷移しているか
	isFadeIn_ = true; // フェードインか
	switchScene_ = false; //シーンを切り替える

	stoppingUpdates_ = false; // 更新を停止する
}

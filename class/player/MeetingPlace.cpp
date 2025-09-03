#include "MeetingPlace.h"
using namespace LWP::Math;

MeetingPlace::MeetingPlace()
	:	sprite_(),
		indexX_(0),
		changeIndexFrameCount_(0),
		position_({ 0.0f,0.0f })
{
	Initialize();
}

MeetingPlace::~MeetingPlace()
{
}

void MeetingPlace::Initialize()
{

	// テクスチャの名前
	const std::string kTextureName = "MeetingPlace.png";
	sprite_.LoadTexture(kTextureName);
	// テクスチャサイズ
	const Vector2& kSize = { 64.0f, 64.0f };
	sprite_.SetSplitSize(kSize);

}

void MeetingPlace::Update()
{

	// indexXの最大値
	const int kIndexMaxX = 6;
	// 連番の切り替わりフレーム数
	const int kChangeIndexFrame = 4;

	// フレームカウントダウン
	--changeIndexFrameCount_;
	if (0 >= changeIndexFrameCount_) {
		// xを移動させる処理
		indexX_ = (++indexX_) % kIndexMaxX;
		// フレームカウントを戻す
		changeIndexFrameCount_ = kChangeIndexFrame;
	}

	// 現在のindexの確定
	sprite_.index = indexX_;

	// Z座標（描画順）
	const float kPositionZ = 0.0f;
	// 位置の移動
	sprite_.worldTF.translation = { position_.x, position_.y, kPositionZ };

}

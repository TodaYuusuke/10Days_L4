#include "MeetingPlace.h"
#include "PlayerGlobalData.h"
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
	sprite_.SetSplitSize(PlayerGlobalData::GetMeetingPlaceTextureSize());

}

void MeetingPlace::Update()
{

	// フレームカウントダウン
	--changeIndexFrameCount_;
	if (0 >= changeIndexFrameCount_) {
		// xを移動させる処理
		indexX_ = (++indexX_) % PlayerGlobalData::GetMeetingPlaceIndexMaxX();
		// フレームカウントを戻す
		changeIndexFrameCount_ = PlayerGlobalData::GetMeetingPlaceChangeIndexFrame();
	}

	// 現在のindexの確定
	sprite_.index = indexX_;
	// 位置の移動
	sprite_.worldTF.translation = { position_.x, position_.y, PlayerGlobalData::GetMeetingPlacePositionZ()};

}

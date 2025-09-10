#include "MeetingPlace.h"
#include "PlayerGlobalData.h"
using namespace LWP::Math;

MeetingPlace::MeetingPlace()
	:	sprite_(),
		indexX_(0),
		changeIndexFrameCount_(0),
		position_({ 0.0f,0.0f })
{
}

MeetingPlace::~MeetingPlace()
{
}

void MeetingPlace::Initialize()
{

	// テクスチャの名前
	const std::string kTextureName = "Flag.png";
	sprite_.LoadTexture(kTextureName);
	// テクスチャサイズ
	sprite_.SetSplitSize(PlayerGlobalData::GetMeetingPlaceTextureSize());
	sprite_.anchorPoint = { 0.12f, 0.92f };
	
	audio_.LoadShortPath("meetingPlace.mp3");

	spriteComeon_.LoadTexture("Comeon.png");

	spriteComeon_.SetSplitSize({256.0f,256.0f});

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

		comeonIndexX_ = (++comeonIndexX_) % 7;

	}

	// 現在のindexの確定
	sprite_.index = indexX_;
	// 位置の移動
	sprite_.worldTF.translation = { position_.x, position_.y, PlayerGlobalData::GetMeetingPlacePositionZ() - 1.0f};

	spriteComeon_.index = comeonIndexX_;
	// 位置の移動
	spriteComeon_.worldTF.translation = { position_.x, position_.y, PlayerGlobalData::GetMeetingPlacePositionZ() };
	spriteComeon_.worldTF.rotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), 0.01f);

}

void MeetingPlace::SetPosition(const LWP::Math::Vector2& position)
{
	position_ = position;
	audio_.Play();
	audio_.SetVolume(0.1f);
}

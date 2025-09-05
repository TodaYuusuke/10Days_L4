#include "MinionSpriteSystem.h"
#include "MinionGlobalData.h"

using namespace LWP::Math;

MinionSpriteSystem::MinionSpriteSystem()
	:	sprite_(),
		indexX_(0),
		preType_(MinionStateType::Idle),
		changeIndexFrameCount_(0)
{

	Initialize();

}

MinionSpriteSystem::~MinionSpriteSystem()
{
}

void MinionSpriteSystem::Initialize()
{

	// テクスチャの名前
	const std::string kTextureName = "Minion.png";
	sprite_.LoadTexture(kTextureName);
	// テクスチャサイズ
	sprite_.SetSplitSize(MinionGlobalData::GetTextureSize());
	// スプライトの大きさ
	sprite_.worldTF.scale = MinionGlobalData::GetSpriteScale();

}

void MinionSpriteSystem::Update(MinionStateType type, const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction)
{

	// indexXの最大値
	const int kIndexMaxX = MinionGlobalData::GetIndexMaxX();
	// 連番の切り替わりフレーム数
	const int kChangeIndexFrame = MinionGlobalData::GetChangeIndexFrame();
	
	// 前の状態のままなら
	if (preType_ == type) {
		// フレームカウントダウン
		--changeIndexFrameCount_;
		if (0 >= changeIndexFrameCount_) {
			// xを移動させる処理
			indexX_ = (++indexX_) % kIndexMaxX;
			// フレームカウントを戻す
			changeIndexFrameCount_ = kChangeIndexFrame;
		}
	}
	else {
		// xを初期化する処理
		indexX_ = 0;
		// フレームカウントを戻す
		changeIndexFrameCount_ = kChangeIndexFrame;
	}

	// 現在のindexの確定
	sprite_.index = static_cast<int>(type) * kIndexMaxX + indexX_;

	// 位置の移動
	sprite_.worldTF.translation = { position.x, position.y, MinionGlobalData::GetPositionZ()};

	// 回転
	const Vector3 kDir3D = { direction.x, direction.y, 0.0f };
	sprite_.worldTF.rotation = Quaternion::ConvertFromTo(Vector3{ 0.0f,1.0f,0.0f }, kDir3D);

	// 大きさ
	sprite_.worldTF.scale = MinionGlobalData::GetSpriteScale();

	// 前状態を切り替え
	preType_ = type;

}

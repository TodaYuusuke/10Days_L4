#include "MinionSpriteSystem.h"

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
	const Vector2& kSize = { 64.0f, 64.0f };
	sprite_.SetSplitSize(kSize);
	// スプライトの大きさ
	sprite_.worldTF.scale = { 0.5f,0.5f,1.0f };

}

void MinionSpriteSystem::Update(MinionStateType type, const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction)
{

	// indexXの最大値
	const int kIndexMaxX = 6;
	// 連番の切り替わりフレーム数
	const int kChangeIndexFrame = 10;
	
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

	// 現在のタイプからyのindexを決定
	const int kIndexY = static_cast<int>(type);
	// 現在のindexの確定
	sprite_.index = kIndexY * kIndexMaxX + indexX_;

	// Z座標（描画順）
	const float kPositionZ = 0.0f;
	// 位置の移動
	sprite_.worldTF.translation = { position.x, position.y, kPositionZ };

	// 回転
	const Vector3 kDir3D = { direction.x, direction.y, 0.0f };
	sprite_.worldTF.rotation = Quaternion::ConvertFromTo(Vector3{ 0.0f,1.0f,0.0f }, kDir3D);

	// 前状態を切り替え
	preType_ = type;

}

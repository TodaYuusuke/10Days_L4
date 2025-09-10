#include "MinionSpriteSystem.h"
#include "MinionGlobalData.h"

using namespace LWP::Math;
using namespace LWP::Info;
using namespace LWP::Utility;

MinionSpriteSystem::MinionSpriteSystem()
	:	sprite_(),
		indexX_(0),
		preType_(MinionStateType::Idle),
		changeIndexFrameCount_(0)
{
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

	// 発光
	lightEmissionSeconds_ -= static_cast<float>(GetDeltaTime());
	if (lightEmissionSeconds_ < 0.0f) {
		lightEmissionSeconds_ = 0.0f;
	}

	float t = lightEmissionSeconds_ / MinionGlobalData::GetLightEmissionSecondMax();
	t = Easing::CallFunction(Easing::Type::Liner, t);
	float r = 255.0f * t + static_cast<float>(color_.R) * (1.0f - t);
	float g = 255.0f * t + static_cast<float>(color_.G) * (1.0f - t);
	float b = 255.0f * t + static_cast<float>(color_.B) * (1.0f - t);
	sprite_.material.color.R = static_cast<unsigned char>(r);
	sprite_.material.color.G = static_cast<unsigned char>(g);
	sprite_.material.color.B = static_cast<unsigned char>(b);

	// 前状態を切り替え
	preType_ = type;

}

void MinionSpriteSystem::ColorChange(int serialNumber)
{

	sprite_.material.color.R = static_cast<unsigned char>(GetRandomFloat(serialNumber) * 255.0f);
	sprite_.material.color.G = static_cast<unsigned char>(GetRandomFloat(serialNumber + 1) * 255.0f);
	sprite_.material.color.B = static_cast<unsigned char>(GetRandomFloat(serialNumber + 2) * 255.0f);

	color_ = sprite_.material.color;

}

void MinionSpriteSystem::LightEmission()
{

	lightEmissionSeconds_ = MinionGlobalData::GetLightEmissionSecondMax();

}

uint32_t MinionSpriteSystem::Hash(uint32_t x) {
	x ^= x >> 16;
	x *= 0x7feb352d;
	x ^= x >> 15;
	x *= 0x846ca68b;
	x ^= x >> 16;
	return x;
}

float MinionSpriteSystem::GetRandomFloat(uint32_t seed) {
	return (Hash(seed) & 0xFFFFFF) / static_cast<float>(1 << 24);
}

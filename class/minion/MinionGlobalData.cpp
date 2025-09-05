#include "MinionGlobalData.h"

// テクスチャサイズ
LWP::Math::Vector2 MinionGlobalData::textureSize_ = { 64.0f,64.0f };
// スプライトサイズ
LWP::Math::Vector3 MinionGlobalData::spriteScale_ = { 0.5f,0.5f,1.0f };
// indexXの最大値
int MinionGlobalData::indexMaxX_ = 6;
// 連番の切り替わりフレーム数
int MinionGlobalData::changeIndexFrame_ = 10;
// Z座標（描画順）
float MinionGlobalData::positionZ_ = 0.0f;
// 移動速度
float MinionGlobalData::speed_ = 0.5f;
// やる気あるときの倍率
float MinionGlobalData::motivationMultiplier_ = 1.5f;
// 攻撃のクールタイム
float MinionGlobalData::attackCoolTimeMax_ = 2.0f;

void MinionGlobalData::JsonDataRegistration(LWP::Utility::JsonIO* jsonIO)
{

	// スプライト関係
	jsonIO->BeginGroup("Sprite").

		// テクスチャサイズ
		AddValue("TextureSize", &textureSize_).
		// スプライトサイズ
		AddValue("SpriteScale", &spriteScale_).
		// indexXの最大値
		AddValue("IndexMaxX", &indexMaxX_).
		// 連番の切り替わりフレーム数
		AddValue("ChangeIndexFrame", &changeIndexFrame_).
		// Z座標（描画順）
		AddValue("PositionZ", &positionZ_).

		EndGroup().

		// 移動ステート関係
		BeginGroup("Move").

		// 移動速度
		AddValue("Speed", &speed_).

		EndGroup().

		// 攻撃ステート関係
		BeginGroup("Attack").

		// やる気あるときの倍率
		AddValue("MotivationMultiplier", &motivationMultiplier_).
		// 攻撃のクールタイム
		AddValue("AttackCoolTimeMax", &attackCoolTimeMax_).

		EndGroup();

}

#include "MinionGlobalData.h"

//初期HP
int MinionGlobalData::initialHp_ = 1;
// 待機状態切り替え距離
float MinionGlobalData::idleStateChangesDistance_ = 10.0f;
// 初期位置
LWP::Math::Vector2 MinionGlobalData::initialPosition_ = { 960.0f, 800.0f };
// 初期位置ランダム幅
LWP::Math::Vector2 MinionGlobalData::initialPositionWidth_ = { 80.0f, 45.0f };
// リクエスト確認時の長さ、追加分
float MinionGlobalData::requestCheckAddLength_ = 20.0f;
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
// 追加移動速度変動
float MinionGlobalData::addSpeedFluctuation_ = 0.5f;
// 追加回転変動
float MinionGlobalData::addRotateFluctuation_ = 0.02f;
// 追加回転最大
float MinionGlobalData::addRotateMax_ = 0.5f;
// やる気あるときの倍率
float MinionGlobalData::motivationMultiplier_ = 1.5f;
// 攻撃のクールタイム
float MinionGlobalData::attackCoolTimeMax_ = 2.0f;
// ダウン時間
float MinionGlobalData::downTime_ = 2.0f;

void MinionGlobalData::JsonDataRegistration(LWP::Utility::JsonIO* jsonIO)
{

	//初期HP
	jsonIO->AddValue("InitialHp", &initialHp_).
		// 待機状態切り替え距離
		AddValue("IdleStateChangesDistance", &idleStateChangesDistance_).
		// 初期位置
		AddValue("InitialPosition", &initialPosition_).
		// 初期位置ランダム幅
		AddValue("InitialPositionWidth", &initialPositionWidth_).
		// リクエスト確認時の長さ、追加分
		AddValue("RequestCheckAddLength", &requestCheckAddLength_).

		// スプライト関係
		BeginGroup("Sprite").

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
		// 集合地点変更時の長さ確認用
		AddValue("AddSpeedFluctuation", &addSpeedFluctuation_).
		// 追加回転変動
		AddValue("AddRotateFluctuation", &addRotateFluctuation_).
		// 追加回転最大
		AddValue("AddRotateMax", &addRotateMax_).

		EndGroup().

		// 攻撃ステート関係
		BeginGroup("Attack").

		// やる気あるときの倍率
		AddValue("MotivationMultiplier", &motivationMultiplier_).
		// 攻撃のクールタイム
		AddValue("AttackCoolTimeMax", &attackCoolTimeMax_).

		EndGroup().

		// ダウンステート関係
		BeginGroup("Down").

		// やる気あるときの倍率
		AddValue("DownTime", &downTime_).

		EndGroup();

}

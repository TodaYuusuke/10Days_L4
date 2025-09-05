#include "PlayerGlobalData.h"

// ドラッグ認定距離
float PlayerGlobalData::dragCertifiedDistance_ = 30.0f;
// スプライトの大きさ	
LWP::Math::Vector3 PlayerGlobalData::mouseSpriteScale_ = {2.0f,2.0f};
// レコーディング時間
float PlayerGlobalData::lineRecordingTime_ = 0.01f;
// 線の長さ最大
float PlayerGlobalData::lineLengthMax_ = 6000.0f;
// Z座標（描画順）
float PlayerGlobalData::linePositionZ_ = 0.0f;
// テクスチャサイズ
LWP::Math::Vector2 PlayerGlobalData::lineTextureSize_ = { 100.0f,100.0f };
// スプライトサイズ
LWP::Math::Vector3 PlayerGlobalData::lineSpriteScale_ = { 0.1f,1.0f,0.0f };
// テクスチャサイズ
LWP::Math::Vector2 PlayerGlobalData::meetingPlaceTextureSize_ = { 64.0f,64.0f };
// スプライトサイズ
LWP::Math::Vector3 PlayerGlobalData::meetingPlaceSpriteScale_ = { 1.0f,1.0f,0.0f };
// indexXの最大値
int PlayerGlobalData::meetingPlaceIndexMaxX_ = 6;
// 連番の切り替わりフレーム数
int PlayerGlobalData::meetingPlaceChangeIndexFrame_ = 4;
// Z座標（描画順）
float PlayerGlobalData::meetingPlacePositionZ_ = 0.0f;
// 壁のHP最大値
int PlayerGlobalData::wallHpMax_ = 1;
// 壁の生存時間最大値
float PlayerGlobalData::wallLifeTimeMax_ = 5.0f;
// Z座標（描画順）
float PlayerGlobalData::wallPositionZ_ = 0.0f;
// テクスチャサイズ
LWP::Math::Vector2 PlayerGlobalData::wallTextureSize_ = { 100.0f,100.0f };
// スプライトの大きさ	
LWP::Math::Vector3 PlayerGlobalData::wallSpriteScale_ = { 1.0f,1.0f,0.0f };

void PlayerGlobalData::JsonDataRegistration(LWP::Utility::JsonIO* jsonIO)
{

	// マウス関係
	jsonIO->BeginGroup("Mouse").

		// ドラッグ認定距離
		AddValue("DragCertifiedDistance", &dragCertifiedDistance_).
		// スプライトの大きさ	
		AddValue("MouseSpriteScale", &mouseSpriteScale_).

		EndGroup().

		//線
		BeginGroup("Line").
		// レコーディング時間
		AddValue("RecordingTime", &lineRecordingTime_).
		// 線の長さ最大
		AddValue("LengthMax", &lineLengthMax_).
		// Z座標（描画順）
		AddValue("PositionZ", &linePositionZ_).
		// テクスチャサイズ
		AddValue("TextureSize", &lineTextureSize_).
		// スプライトの大きさ
		AddValue("SpriteScale", &lineSpriteScale_).

		EndGroup().

		// 集合場所関係
		BeginGroup("MeetingPlace").

		// テクスチャサイズ
		AddValue("TextureSize", &meetingPlaceTextureSize_).
		// スプライトの大きさ
		AddValue("SpriteScale", &meetingPlaceSpriteScale_).
		// indexXの最大値
		AddValue("IndexMaxX", &meetingPlaceIndexMaxX_).
		// 連番の切り替わりフレーム数
		AddValue("ChangeIndexFrame", &meetingPlaceChangeIndexFrame_).
		// Z座標（描画順）
		AddValue("PositionZ", &meetingPlacePositionZ_).

		EndGroup().

		// 壁関係
		BeginGroup("Wall").

		// 壁のHP最大値
		AddValue("HpMax", &wallHpMax_).
		// 壁の生存時間最大値
		AddValue("LifeTimeMax", &wallLifeTimeMax_).
		// Z座標（描画順）
		AddValue("PositionZ", &wallPositionZ_).
		// テクスチャサイズ
		AddValue("TextureSize", &wallTextureSize_).
		// スプライトの大きさ	
		AddValue("SpriteScale", &wallSpriteScale_).

		EndGroup();

}

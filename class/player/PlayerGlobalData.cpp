#include "PlayerGlobalData.h"

// ドラッグ認定距離
float PlayerGlobalData::dragCertifiedDistance_ = 30.0f;
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

void PlayerGlobalData::JsonDataRegistration(LWP::Utility::JsonIO* jsonIO)
{

	// マウス関係
	jsonIO->BeginGroup("Mouse").

		// ドラッグ認定距離
		AddValue("DragCertifiedDistance", &dragCertifiedDistance_).

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

		EndGroup();

}

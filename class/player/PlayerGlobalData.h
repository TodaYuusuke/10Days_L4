#pragma once
#include <Adapter.h>
/// <summary>
/// プレイヤーのグローバルデータ
/// </summary>
class PlayerGlobalData
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerGlobalData() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerGlobalData() = default;

	/// <summary>
	/// JSON登録
	/// </summary>
	/// <param name="jsonIO">jsonIO</param>
	static void JsonDataRegistration(LWP::Utility::JsonIO* jsonIO);

public: // アクセッサ

	static float GetDragCertifiedDistance() { return dragCertifiedDistance_; }

	static float GetLineRecordingTime() { return lineRecordingTime_; }
	static float GetLineLengthMax() { return lineLengthMax_; }
	static float GetLinePositionZ() { return linePositionZ_; }
	static LWP::Math::Vector2 GetLineTextureSize() { return lineTextureSize_; }
	static LWP::Math::Vector3 GetLineSpriteScale() { return lineSpriteScale_; }

	static LWP::Math::Vector2 GetMeetingPlaceTextureSize() { return meetingPlaceTextureSize_; }
	static LWP::Math::Vector3 GetMeetingPlaceSpriteScale() { return meetingPlaceSpriteScale_; }
	static int GetMeetingPlaceIndexMaxX() { return meetingPlaceIndexMaxX_; }
	static int GetMeetingPlaceChangeIndexFrame() { return meetingPlaceChangeIndexFrame_; }
	static float GetMeetingPlacePositionZ() { return meetingPlacePositionZ_; }

private: //メンバ変数

	// マウス関係

	// ドラッグ認定距離
	static float dragCertifiedDistance_;

	//線

	// レコーディング時間
	static float lineRecordingTime_;
	// 線の長さ最大
	static float lineLengthMax_;
	// Z座標（描画順）
	static float linePositionZ_;
	// テクスチャサイズ
	static LWP::Math::Vector2 lineTextureSize_;
	// スプライトの大きさ	
	static LWP::Math::Vector3 lineSpriteScale_;

	// 集合場所関係

	// テクスチャサイズ
	static LWP::Math::Vector2 meetingPlaceTextureSize_;
	// スプライトの大きさ
	static LWP::Math::Vector3 meetingPlaceSpriteScale_;
	// indexXの最大値
	static int meetingPlaceIndexMaxX_;
	// 連番の切り替わりフレーム数
	static int meetingPlaceChangeIndexFrame_;
	// Z座標（描画順）
	static float meetingPlacePositionZ_;

};


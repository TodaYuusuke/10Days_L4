#pragma once
#include <Adapter.h>

/// <summary>
/// 石のグローバルデータ
/// </summary>
class StoneGlobalData
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StoneGlobalData() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StoneGlobalData() = default;

	/// <summary>
	/// JSON登録
	/// </summary>
	/// <param name="jsonIO">jsonIO</param>
	static void JsonDataRegistration(LWP::Utility::JsonIO* jsonIO);

public: // アクセッサ

	// 加速度
	static float GetAcceleration() { return acceleration_; }
	// 初速
	static float GetInitialSpeed() { return initialSpeed_; }
	// Z座標
	static float GetPositionZ() { return positionZ_; }
	// スプライトの大きさ	
	static LWP::Math::Vector3 GetSpriteScale() { return spriteScale_; }

private:

	// 加速度
	static float acceleration_;
	// 初速
	static float initialSpeed_;
	// Z座標
	static float positionZ_;
	// スプライトの大きさ	
	static LWP::Math::Vector3 spriteScale_;

};


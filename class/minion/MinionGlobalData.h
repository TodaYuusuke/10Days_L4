#pragma once
#include <Adapter.h>
/// <summary>
/// 手下のグローバルデータ
/// </summary>
class MinionGlobalData
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MinionGlobalData() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MinionGlobalData() = default;

	/// <summary>
	/// JSON登録
	/// </summary>
	/// <param name="jsonIO">jsonIO</param>
	static void JsonDataRegistration(LWP::Utility::JsonIO* jsonIO);

public: // アクセッサ

	static int GetInitialHp() { return initialHp_; }
	static float GetIdleStateChangesDistance() { return idleStateChangesDistance_; }
	static LWP::Math::Vector2 GetInitialPosition() { return initialPosition_; }
	static LWP::Math::Vector2 GetInitialPositionWidth() { return initialPositionWidth_; }
	static float GetRequestCheckAddLength() { return requestCheckAddLength_; }
	static LWP::Math::Vector2 GetTextureSize() { return textureSize_; }
	static LWP::Math::Vector3 GetSpriteScale() { return spriteScale_; }
	static int GetIndexMaxX() { return indexMaxX_; }
	static int GetChangeIndexFrame() { return changeIndexFrame_; }
	static float GetPositionZ() { return positionZ_; }
	static float GetSpeed() { return speed_; }
	static float GetAddSpeedFluctuation() { return addSpeedFluctuation_; }
	static float GetAddRotateFluctuation() { return addRotateFluctuation_; }
	static float GetAddRotateMax() { return addRotateMax_; }
	static float GetMotivationMultiplier() { return motivationMultiplier_; }
	static float GetAttackCoolTimeMax() { return attackCoolTimeMax_; }
	static float GetDownTime() { return downTime_; }

private: //メンバ変数
	
	// 初期HP
	static int initialHp_;
	// 待機状態切り替え距離
	static float idleStateChangesDistance_;
	// 初期位置
	static LWP::Math::Vector2 initialPosition_;
	// 初期位置ランダム幅
	static LWP::Math::Vector2 initialPositionWidth_;
	// リクエスト確認時の長さ、追加分
	static float requestCheckAddLength_;

	// スプライト関係

	// テクスチャサイズ
	static LWP::Math::Vector2 textureSize_;
	// スプライトサイズ
	static LWP::Math::Vector3 spriteScale_;
	// indexXの最大値
	static int indexMaxX_;
	// 連番の切り替わりフレーム数
	static int changeIndexFrame_;
	// Z座標（描画順）
	static float positionZ_;

	// 移動ステート関係

	// 移動速度
	static float speed_;
	// 追加移動速度変動
	static float addSpeedFluctuation_;
	// 追加回転変動
	static float addRotateFluctuation_;
	// 追加回転最大
	static float addRotateMax_;

	// 攻撃ステート関係

	// やる気あるときの倍率
	static float motivationMultiplier_;
	// 攻撃のクールタイム
	static float attackCoolTimeMax_;

	// ダウンステート関係

	// ダウン時間
	static float downTime_;

};


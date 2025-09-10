#pragma once
#include <Adapter.h>
#include "state/MinionStateType.h"

// 前方宣言
class Minion;

/// <summary>
/// 手下のスプライト機能
/// </summary>
class MinionSpriteSystem
{

public:  // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MinionSpriteSystem();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MinionSpriteSystem();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="type">状態</param>
	/// <param name="position">位置</param>
	/// <param name="direction">方向ベクトル</param>
	void Update(MinionStateType type, const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction);

	/// <summary>
	/// 色を変える
	/// </summary>
	/// <param name="serialNumber">シリアルナンバー</param>
	void ColorChange(int serialNumber);

	/// <summary>
	/// 発光
	/// </summary>
	void LightEmission();

public:

	// スプライト
	LWP::Primitive::SequenceSprite& GetSprite() { return sprite_; }
	const LWP::Primitive::SequenceSprite& GetSprite() const { return sprite_; }

private:

	/// <summary>
	/// ハッシュ
	/// </summary>
	/// <param name="x">値</param>
	/// <returns></returns>
	uint32_t Hash(uint32_t  x);

	/// <summary>
	/// 乱数
	/// </summary>
	/// <param name="seed">シード</param>
	/// <returns></returns>
	float GetRandomFloat(uint32_t  seed);

private: // メンバ変数

	// スプライト
	LWP::Primitive::SequenceSprite sprite_;

	// 連番のindexX
	int indexX_;

	// 前の状態
	MinionStateType preType_;

	// index変更までのフレームカウント
	int changeIndexFrameCount_;

	// 発光秒数
	float lightEmissionSeconds_;

	LWP::Utility::Color color_;

};


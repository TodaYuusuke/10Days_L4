#pragma once
#include <Adapter.h>
#include "state/MinionStateType.h"

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

private: // メンバ変数

	// スプライト
	LWP::Primitive::SequenceSprite sprite_;

	// 連番のindexX
	int indexX_;

	// 前の状態
	MinionStateType preType_;

	// index変更までのフレームカウント
	int changeIndexFrameCount_;

};


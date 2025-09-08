#pragma once
#include <Adapter.h>
#include <memory>
#include "../minion/MinionSpriteSystem.h"
#include "../stone/Stone.h"

/// <summary>
/// タイトルミニオン
/// </summary>
class TitleMinion
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleMinion();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleMinion();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバッグ用GUI
	/// </summary>
	void DebugGUI();

private:

	// スプライトシステム
	MinionSpriteSystem spriteSystem_;

	// 位置
	LWP::Math::Vector2 position_;
	// 回転、方向 
	LWP::Math::Vector2 direction_;

	// 石
	Stone stone_;
	// やる気タイム
	float motivationTime_;
	// 石を投げるまでの時間
	float attackCoolTime_;

};


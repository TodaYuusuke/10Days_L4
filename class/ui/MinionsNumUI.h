#pragma once
#include <Adapter.h>
#include "BaseUI.h"

// 前方宣言
class MinionManager;

/// <summary>
/// 手下の数UI
/// </summary>
class MinionsNumUI :
	public BaseUI
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MinionsNumUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MinionsNumUI() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 全部のisActiveを変更する関数
	/// </summary>
	/// <param name="isActive"></param>
	void SetIsActive(bool isActive) override;

	/// <summary>
	/// JSON登録
	/// </summary>
	/// <param name="jsonIO">json</param>
	void JsonDataRegistration(LWP::Utility::JsonIO* jsonIO) override;

public: // アクセッサ

	void SetMinionManager(MinionManager* minionManager) { minionManager_ = minionManager; }

private: // メンバ変数

	// スプライト 百の位
	LWP::Primitive::SequenceSprite spriteLeftNum_;
	// スプライト 十の位
	LWP::Primitive::SequenceSprite spriteCenterNum_;
	// スプライト 一の位
	LWP::Primitive::SequenceSprite spriteRightNum_;
	// スプライト 手下マーク
	LWP::Primitive::NormalSprite spriteMark_;

public:

	//	手下のマネージャー
	MinionManager* minionManager_;

};


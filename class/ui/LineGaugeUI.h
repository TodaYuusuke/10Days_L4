#pragma once
#include "BaseUI.h"

// 前方宣言
class Player;

/// <summary>
/// 線のゲージ
/// </summary>
class LineGaugeUI :
    public BaseUI
{

public: 

	/// <summary>
	/// コンストラクタ
	/// </summary>
	LineGaugeUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LineGaugeUI() override;

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

	void SetPlayer(Player* player) { player_ = player; }

private: // メンバ変数
	
	// 入れ物
	LWP::Primitive::NormalSprite containerSprite_;
	// ゲージ
	LWP::Primitive::ClipSprite  gaugeSprite_;

private: // ポインタ

	// プレイヤー
	Player* player_;

};


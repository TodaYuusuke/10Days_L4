#pragma once
#include "BaseUI.h"

// 前方宣言
class EnemyManager;

/// <summary>
/// ボスHPUI
/// </summary>
class BossHPUI :
    public BaseUI
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BossHPUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossHPUI() override;

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

	void SetEnemyManager(EnemyManager* enemyManager) { enemyManager_ = enemyManager; }

public:

    // 入れ物
    LWP::Primitive::NormalSprite containerSprite_;
    // ゲージ
    LWP::Primitive::ClipSprite  gaugeSprite_;

private:

    // エネミーマネージャー
    EnemyManager* enemyManager_;

};


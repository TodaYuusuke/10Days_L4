#pragma once
#include <array>
#include <memory>
#include "BaseUI.h"
#include "UIList.h"

// 前方宣言
class Player;
class MinionManager;
class EnemyManager;

/// <summary>
/// UI管理クラス
/// </summary>
class UIManager
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIManager();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="minionManager">手下のマネージャー</param>
	/// <param name="minionManager">エネミーマネージャー</param>
	UIManager(Player* player, MinionManager* minionManager, EnemyManager* enemyManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UIManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="minionManager">手下のマネージャー</param>
	/// <param name="minionManager">エネミーマネージャー</param>
	void Initialize(Player* player, MinionManager* minionManager, EnemyManager* enemyManager);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private: // メンバ変数

	// UI
	std::array<std::unique_ptr<BaseUI>, static_cast<size_t>(UIList::UIListOfCount)> uis_;

	// json
	LWP::Utility::JsonIO jsonIO_;

};


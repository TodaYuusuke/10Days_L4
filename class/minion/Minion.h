#pragma once

#include <unordered_map>
#include <memory>
#include "state/IMinionState.h"
#include "state/MinionStateType.h"
#include "MinionSpriteSystem.h"

// 前方宣言
class MinionManager;

/// <summary>
/// 手下クラス
/// </summary>
class Minion final
{

public: 

	// シリアルナンバー生成用
	static int serialNumberCount_;

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Minion();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="minionManager">ミニオンマネージャー</param>
	Minion(MinionManager* minionManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Minion();

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

	/// <summary>
	/// ステータス変更
	/// </summary>
	/// <param name="newStateType">新しい状態</param>
	void ChangeState(MinionStateType newStateType);

public: // アクセッサ

	LWP::Math::Vector2 GetPositon() const { return positon_; }
	int GetHp() const { return hp_; }
	int GetSerialNumber() const { return serialNumber_; }

	void SetPositon(const LWP::Math::Vector2& positon) { positon_ = positon; }
	void SetDirection(const LWP::Math::Vector2& direction) { direction_ = direction; }

	MinionManager* GetMinionManager() { return minionManager_; }

private: // メンバ変数

	// ステータス
	std::unordered_map<MinionStateType, std::unique_ptr<IMinionState>> stateMap_;
	// 現在の状態
	IMinionState* currentState_ = nullptr;
	// ステートパターン
	LWP::Utility::StatePattern<MinionStateType, static_cast<size_t>(MinionStateType::StateTypeOfCount)> statePattern_;

	// スプライトシステム
	std::unique_ptr<MinionSpriteSystem> spriteSystem_;

	// 位置
	LWP::Math::Vector2 positon_;
	// 回転、方向 
	LWP::Math::Vector2 direction_;
	// HP
	int hp_;
	// 手下番号
	int serialNumber_;

private: // ポインタ

	// マネージャー
	MinionManager* minionManager_;

};


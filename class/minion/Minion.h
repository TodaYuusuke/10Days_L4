#pragma once

#include <unordered_map>
#include <memory>
#include "state/IMinionState.h"
#include "state/MinionStateType.h"
#include "MinionSpriteSystem.h"

/// <summary>
/// 手下クラス
/// </summary>
class Minion final
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Minion();

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
	// 回転 ラジアン角
	float radian_;
	// HP
	int hp_;

};


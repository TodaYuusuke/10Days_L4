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
	/// 石を投げる
	/// </summary>
	void ThrowStone();

private: // メンバ関数

	/// <summary>
	/// ステータス変更
	/// </summary>
	/// <param name="newStateType">新しい状態</param>
	void ChangeState(MinionStateType newStateType);

public: // アクセッサ

	LWP::Math::Vector2 GetPosition() const { return position_; }
	int GetHp() const { return hp_; }
	int GetSerialNumber() const { return serialNumber_; }
	MinionStateType GetCurrentStateType() const { return currentStateType_; }

	void SetRequestStateType(MinionStateType requestStateType) { requestStateType_ = requestStateType; }
	void SetPosition(const LWP::Math::Vector2& position) { position_ = position; }
	void SetDirection(const LWP::Math::Vector2& direction) { direction_ = direction; }

	MinionManager* GetMinionManager() { return minionManager_; }
	void SetMinionManager(MinionManager* minionManager) { minionManager_ = minionManager; }

	float GetMotivationTime() const { return motivationTime_; }
	void SetMotivationTime(float motivationTime) { motivationTime_ = motivationTime; }

	// スプライト
	MinionSpriteSystem& GetSprite() { return spriteSystem_; }
	const MinionSpriteSystem& GetSprite() const { return spriteSystem_; }

	// スプライト
	LWP::Object::Collision2D& GetCollider() { return collider_; }
	const LWP::Object::Collision2D& GetCollider() const { return collider_; }

	bool GetInvincible() const { return invincible_; }
	void SetInvincible(bool invincible) { invincible_ = invincible; }

private: // メンバ変数

	// ステータス
	std::unordered_map<MinionStateType, std::unique_ptr<IMinionState>> stateMap_;
	// 現在の状態
	IMinionState* currentState_ = nullptr;
	// 現在の状態
	MinionStateType currentStateType_;
	// リクエストされた状態
	MinionStateType requestStateType_;

	// スプライトシステム
	MinionSpriteSystem spriteSystem_;

	// 位置
	LWP::Math::Vector2 position_;
	LWP::Math::Vector2 prevPosition_;
	// 回転、方向 
	LWP::Math::Vector2 direction_;
	// HP
	int hp_;
	// 手下番号
	int serialNumber_;

	// やる気タイム
	float motivationTime_;
	// 無敵
	bool invincible_;

	// コライダー
	LWP::Object::Collision2D collider_;

private: // ポインタ

	// マネージャー
	MinionManager* minionManager_;

};


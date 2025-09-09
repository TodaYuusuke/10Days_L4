#pragma once
#include "Minion.h"
#include "../player/MeetingPlace.h"
#include "../stone/StoneManager.h"
#include "../boss/EnemyManager.h"

/// <summary>
/// 手下の管理クラス
/// </summary>
class MinionManager
{

public:

	// ミニオンの数
	static const size_t kMinionNumMax_ = 100;

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MinionManager();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="meetingPlace">集合場所</param>
	/// <param name="stoneManager">石マネージャー</param>
	/// <param name="enemyManager">エネミーマネージャー</param>
	MinionManager(MeetingPlace* meetingPlace, StoneManager* stoneManager, EnemyManager* enemyManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MinionManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

public: // アクセッサ

	void ApplyMinionAttack(int i) {
		minions_[i]->SetRequestStateType(MinionStateType::Attack);
	}

	MeetingPlace* GetMeetingPlace() { return meetingPlace_; }
	StoneManager* GetStoneManager() { return stoneManager_; }
	EnemyManager* GetEnemyManager() { return enemyManager_; }

	std::array<LWP::Math::Vector2, kMinionNumMax_> GetMinionsPosition() { return minionsPosition_; }
	size_t GetMinionNum() const { return minionNum_; }
	size_t GetAttackMinionNum() const { return attackMinionNum_; }
	LWP::Math::Vector2 GetTargetPosition() const { return targetPosition_; }

private:

	// 手下たち
	std::array<std::unique_ptr<Minion>, kMinionNumMax_> minions_;
	std::array<LWP::Math::Vector2, kMinionNumMax_> minionsPosition_;

	// 残りの手下たち
	size_t minionNum_;

	// 攻撃している手下たち
	size_t attackMinionNum_;

	// 目指す場所
	LWP::Math::Vector2 targetPosition_;

	// json
	LWP::Utility::JsonIO jsonIO_;

private: // ポインタ

	// 集合場所
	MeetingPlace* meetingPlace_;

	// 石マネージャー(なげるため)
	StoneManager* stoneManager_;

	// エネミーマネージャー
	EnemyManager* enemyManager_;

};


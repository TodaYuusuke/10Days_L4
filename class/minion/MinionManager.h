#pragma once
#include "Minion.h"
#include "../player/MeetingPlace.h"

/// <summary>
/// 手下の管理クラス
/// </summary>
class MinionManager
{

public:

	// ミニオンの数
	static const size_t kMinionNumMax_ = 10;

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MinionManager();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="meetingPlace">集合場所</param>
	MinionManager(MeetingPlace* meetingPlace);

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

	MeetingPlace* GetMeetingPlace() { return meetingPlace_; }

private:

	// 手下たち
	std::array<std::unique_ptr<Minion>, kMinionNumMax_> minions_;

	// 残りの手下たち
	size_t minionNum_;

private: // ポインタ

	// 集合場所
	MeetingPlace* meetingPlace_;

};


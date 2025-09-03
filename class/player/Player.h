#pragma once
#include <Adapter.h>
#include "MeetingPlace.h"
#include "PlayerMouseOperation.h"

/// <summary>
/// プレイヤー
/// </summary>
class Player
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private:
	
	// マウスの操作
	std::unique_ptr<PlayerMouseOperation> playerMouseOperation_;

	// 集合場所
	std::unique_ptr<MeetingPlace> meetingPlace_;

};


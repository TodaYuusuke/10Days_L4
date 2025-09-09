#pragma once
#include <Adapter.h>
#include "MeetingPlace.h"
#include "PlayerMouseOperation.h"
#include "Drawing.h"
#include "wall/WallManager.h"

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

	/// <summary>
	/// drawing_に手下のマネージャーを設定する
	/// </summary>
	/// <param name="minionManager"></param>
	void SetMinionManagerForDrawing(MinionManager* minionManager);

public: // アクセッサ

	MeetingPlace* GetMeetingPlace() { return &meetingPlace_; }
	Drawing* GetDrawing() { return &drawing_; }

private:
	
	// マウスの操作
	PlayerMouseOperation playerMouseOperation_;

	// 集合場所
	MeetingPlace meetingPlace_;

	// 書き途中
	Drawing drawing_;

	// 壁マネージャー
	WallManager wallManager_;

	// json
	LWP::Utility::JsonIO jsonIO_;

};


#pragma once
#include <list>
#include "Stone.h"

/// <summary>
/// 石の管理クラス
/// </summary>
class StoneManager
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StoneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StoneManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 壁を作成
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="direction">方向</param>
	void CreateStone(const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction);

private:

	// 壁
	std::list<Stone*> stones_;
	// json
	LWP::Utility::JsonIO jsonIO_;

	bool isCreate_;

	LWP::Resource::Audio audio_[3];

};


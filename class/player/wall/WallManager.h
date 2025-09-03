#pragma once
#include <list>
#include "Wall.h"

/// <summary>
/// 壁の管理者
/// </summary>
class WallManager
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	WallManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~WallManager();

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
	/// <param name="points">点</param>
	void CreateWalls(const std::vector<LWP::Math::Vector2>* points);

private:

	// 壁
	std::list<Wall*> walls_;

	// 壁のHP最大値
	int hpMax_;

	// 壁の生存時間最大値
	float lifeTimeMax_;

};


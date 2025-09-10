#pragma once
#include <list>
#include "Wall.h"

class EnemyManager;

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

public:

	void SetEnemyManager(EnemyManager* enemyManager) { enemyManager_ = enemyManager; }
	EnemyManager* GetEnemyManager() { return enemyManager_; }

private:

	// 壁
	std::list<Wall*> walls_;

private:

	EnemyManager* enemyManager_;

};


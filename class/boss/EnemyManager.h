#pragma once
#include "BaseEnemy.h"

// 敵用の管理クラス シングルトン扱いでGameSceneのみ生成
class EnemyManager {
public:
	EnemyManager()= default;
	~EnemyManager() = default;

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// アニメーションや衝突判定などの二次更新
	void SecondUpdate();

private:
	// 敵のコンテナ
	std::vector<std::unique_ptr<BaseEnemy>> enemies_;

};

#pragma once
#include "BaseEnemy.h"

// 敵用の管理クラス シングルトン扱いでGameSceneのみ生成
class EnemyManager {
public:
	EnemyManager();
	~EnemyManager() = default;

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// アニメーションや衝突判定などの二次更新
	void SecondUpdate();

	// 敵の座標 現在敵が1体しかいないため、くそ定義してる
	const LWP::Math::Vector2& GetEnemyPosition() const;
	// 敵の攻撃力ptt くそ定義
	const int* GetEnemyAttackPowerPtr() const;

private:
	// 敵のコンテナ
	std::vector<std::unique_ptr<BaseEnemy>> enemies_;

};

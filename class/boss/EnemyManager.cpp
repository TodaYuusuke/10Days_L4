#include "EnemyManager.h"
#include "normalBoss/NormalBoss.h"

void EnemyManager::Initialize() {
	enemies_.push_back(std::make_unique<NormalBoss>());
}

void EnemyManager::Update() {
	// enemyの状態など通常更新処理

	for (auto& enemy : enemies_) {
		enemy->Update();
	}

}

void EnemyManager::SecondUpdate() {
	// 衝突判定等での座標処理


	// アニメーション等の描画更新処理

}

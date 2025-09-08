#include "EnemyManager.h"
#include "normalBoss/NormalBoss.h"
#include "data/EnemyDataManager.h"

EnemyManager::EnemyManager() {
	Initialize();
}

void EnemyManager::Initialize() {
	EnemyDataManager::GetInstance()->Initialize();
	auto normalBossData = EnemyDataManager::GetInstance()->GetData(BaseEnemyData::Type::NormalBoss);
	enemies_.push_back(std::make_unique<NormalBoss>(*normalBossData));

}
void EnemyManager::Update() {
	
	EnemyDataManager::GetInstance()->ImGuiProc();

	// enemyの状態など通常更新処理
	for (auto& enemy : enemies_) {
		enemy->Update();
	}

}

void EnemyManager::SecondUpdate() {
	// 衝突判定等での座標処理


	// アニメーション等の描画更新処理

}

const LWP::Math::Vector2& EnemyManager::GetEnemyPosition() const {
	return enemies_.at(0)->corePosition_;
}

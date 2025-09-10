#include "EnemyManager.h"
#include "normalBoss/NormalBoss.h"
#include "data/EnemyDataManager.h"
#include "../minion/MinionManager.h"

EnemyManager::EnemyManager() {
	
}

void EnemyManager::Initialize() {
	EnemyDataManager::GetInstance()->Initialize();
	auto normalBossData = EnemyDataManager::GetInstance()->GetData(BaseEnemyData::Type::NormalBoss);
	enemies_.push_back(std::make_unique<NormalBoss>(*normalBossData));

	NormalBoss* nBoss = dynamic_cast<NormalBoss*>(enemies_[0].get());
	nBoss->SetMinionManagerPtr(minionManager_);

	nBoss->Initialize(*normalBossData);

}
void EnemyManager::Update() {
	
	EnemyDataManager::GetInstance()->ImGuiProc();

	// enemyの状態など通常更新処理
	for (auto& enemy : enemies_) {
		if (!enemy->GetIsAlive()) { continue; }
		enemy->Update();
	}

}

void EnemyManager::SecondUpdate() {
	// 衝突判定等での座標処理

	// アニメーション等の描画更新処理

}

void EnemyManager::SetMinionManagerPtr(MinionManager* manager) {
	minionManager_ = manager;
}

const LWP::Math::Vector2& EnemyManager::GetEnemyPosition() const {
	return enemies_.at(0)->corePosition_;
}

const int* EnemyManager::GetEnemyAttackPowerPtr() const {
	return enemies_.at(0)->GetAttackPowerPtr();
}

const int& EnemyManager::GetEnemyHp(int* max) const {
	if (max != nullptr) {
		*max = *enemies_.at(0)->GetMaxHpPtr();
	}
	return *enemies_.at(0)->GetHpPtr();
}

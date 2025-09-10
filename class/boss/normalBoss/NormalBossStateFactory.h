#pragma once
#include <unordered_map>
#include "NormalBossStateType.h"
#include "../data/EnemyDataManager.h"
#include "../data/NormalBossData.h"
#include "../state/IEnemyState.h"

class NormalBossStateManager;
class EnemyBullet;
class MinionManager;

namespace StateFactory::NormalBoss {
	/// <summary>
	/// 状態作成関数
	/// </summary>
	/// <returns>状態一覧</returns>
	std::unordered_map<uint8_t, std::unique_ptr<IEnemyState>> CreateStates(const NormalBossData* data, 
		NormalBossStateManager* sManeger, std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax>* bullets,
		MinionManager* mManager);
}
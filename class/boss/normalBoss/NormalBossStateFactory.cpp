#include "NormalBossStateFactory.h"
#include "../state/EnemyIdleState.h"
#include "../state/EnemyMoveState.h"
#include "NormalBossStateManager.h"

std::unordered_map<uint8_t, std::unique_ptr<IEnemyState>> StateFactory::NormalBoss::CreateStates(const NormalBossData* data, NormalBossStateManager* sManager) {
	std::unordered_map<uint8_t, std::unique_ptr<IEnemyState>> states;
	sManager;
	states[static_cast<uint8_t>(NormalBossStateType::Idle)] = std::make_unique<EnemyIdleState>(&data->idleTime, sManager);
	states[static_cast<uint8_t>(NormalBossStateType::Move)] = std::make_unique<EnemyMoveState>(&data->moveSpeed, sManager);
	states[static_cast<uint8_t>(NormalBossStateType::StateTypeOfCount)] = nullptr;

	return states;
}

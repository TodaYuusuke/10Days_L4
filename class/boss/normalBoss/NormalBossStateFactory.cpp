#include "NormalBossStateFactory.h"
#include "../state/EnemyIdleState.h"
#include "../state/EnemyMoveState.h"

std::unordered_map<uint8_t, std::unique_ptr<IEnemyState>> StateFactory::NormalBoss::CreateStates() {
	std::unordered_map<uint8_t, std::unique_ptr<IEnemyState>> states;

	states[static_cast<uint8_t>(NormalBossStateType::Idel)] = std::make_unique<EnemyIdleState>();
	states[static_cast<uint8_t>(NormalBossStateType::Move)] = std::make_unique<EnemyMoveState>();
	states[static_cast<uint8_t>(NormalBossStateType::StateTypeOfCount)] = nullptr;

	return states;
}

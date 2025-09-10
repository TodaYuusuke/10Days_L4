#include "NormalBossStateFactory.h"
#include "../state/EnemyIdleState.h"
#include "../state/EnemyMoveState.h"
#include "../state/NormalEnemySlamState.h"
#include "../state/BarrageAttackState.h"
#include "../state/RainBarrage.h"
#include "../state/CircleBarrageState.h"
#include "NormalBossStateManager.h"
#include "../../minion/MinionManager.h"

std::unordered_map<uint8_t, std::unique_ptr<IEnemyState>> StateFactory::NormalBoss::CreateStates(
	const NormalBossData* data, NormalBossStateManager* sManager, std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax>* bullets,
	MinionManager* mManager) {
	std::unordered_map<uint8_t, std::unique_ptr<IEnemyState>> states;
	states[static_cast<uint8_t>(NormalBossStateType::Idle)] = std::make_unique<EnemyIdleState>(&data->idleTime, sManager, mManager);
	states[static_cast<uint8_t>(NormalBossStateType::Move)] = std::make_unique<EnemyMoveState>(&data->moveSpeed, sManager);
	states[static_cast<uint8_t>(NormalBossStateType::Slam)] = std::make_unique<NormalEnemySlamState>(data, sManager);
	states[static_cast<uint8_t>(NormalBossStateType::Barrage)] = std::make_unique<BarrageAttackState>(data, sManager, bullets);
	states[static_cast<uint8_t>(NormalBossStateType::Rain)] = std::make_unique<RainBarrageState>(data, sManager, bullets);
	states[static_cast<uint8_t>(NormalBossStateType::Circle)] = std::make_unique<CircleBarrageState>(data, sManager, bullets);
	states[static_cast<uint8_t>(NormalBossStateType::StateTypeOfCount)] = nullptr;

	return states;
}

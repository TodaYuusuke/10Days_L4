#include "MinionStateFactory.h"
#include "MinionIdleState.h"
#include "MinionMoveState.h"

std::unordered_map<MinionStateType, std::unique_ptr<IMinionState>> MinionStateFactory::CreateStates()
{

    std::unordered_map<MinionStateType, std::unique_ptr<IMinionState>> states;

    states[MinionStateType::Idle] = std::make_unique<MinionIdleState>();
    states[MinionStateType::Move] = std::make_unique<MinionMoveState>();
    states[MinionStateType::StateTypeOfCount] = nullptr;

    return states;

}

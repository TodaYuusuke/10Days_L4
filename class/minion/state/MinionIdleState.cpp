#include "MinionIdleState.h"
#include "../Minion.h"
#include "../MinionManager.h"
#include "../MinionGlobalData.h"
using namespace LWP::Math;
using namespace LWP::Utility;

void MinionIdleState::Enter(Minion* minion)
{
}

void MinionIdleState::Update(Minion* minion)
{

    MinionManager* minionManager = minion->GetMinionManager();
    // リクエスト
    Vector2 sub = (minionManager->GetTargetPosition() - minion->GetPosition());
    //倍率
    const float kDistanceMagnification = static_cast<float>(minionManager->GetAttackMinionNum()) / static_cast<float>(minionManager->kMinionNumMax_);
    // リクエスト決定
    if (sub.Length() > (MinionGlobalData::GetIdleStateChangesDistance() * Easing::CallFunction(Easing::Type::OutExpo, kDistanceMagnification)) + MinionGlobalData::GetRequestCheckAddLength()) {
        minion->SetRequestStateType(MinionStateType::Move);
    }

}

void MinionIdleState::Exit(Minion* minion)
{
    minion;
}

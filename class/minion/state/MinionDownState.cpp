#include "MinionDownState.h"
#include "../Minion.h"
#include "../MinionGlobalData.h"
using namespace LWP::Info;

void MinionDownState::Enter(Minion* minion)
{

	remainingTime_ = MinionGlobalData::GetDownTime();

}

void MinionDownState::Update(Minion* minion)
{

	// 残り時間
	remainingTime_ -= static_cast<float>(GetDeltaTime());

	if (remainingTime_ <= 0.0f) {
		// 確認のため移動状態をリクエスト
		minion->SetRequestStateType(MinionStateType::Move);
	}
		
}

void MinionDownState::Exit(Minion* minion)
{
}

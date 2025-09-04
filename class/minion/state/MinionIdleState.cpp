#include "MinionIdleState.h"
#include "../Minion.h"

void MinionIdleState::Enter(Minion* minion)
{

	// 確認のため移動状態をリクエスト
	minion->SetRequestStateType(MinionStateType::Move);

}

void MinionIdleState::Update(Minion* minion)
{
}

void MinionIdleState::Exit(Minion* minion)
{
}

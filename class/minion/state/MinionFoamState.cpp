#include "MinionFoamState.h"
#include "../Minion.h"

void MinionFoamState::Enter(Minion* minion)
{
}

void MinionFoamState::Update(Minion* minion)
{
}

void MinionFoamState::Exit(Minion* minion)
{

	minion->SetHp(1);

}

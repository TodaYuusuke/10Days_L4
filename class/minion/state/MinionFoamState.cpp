#include "MinionFoamState.h"
#include "../Minion.h"

void MinionFoamState::Enter(Minion* minion)
{
	minion;
}

void MinionFoamState::Update(Minion* minion)
{
	minion;
}

void MinionFoamState::Exit(Minion* minion)
{

	minion->SetHp(1);

}

#include "MinionAbsorbState.h"
#include "../Minion.h"

void MinionAbsorbState::Enter(Minion* minion)
{
	minion->GetSprite().GetSprite().isActive = false;
	minion->GetCollider().isActive = false;
}

void MinionAbsorbState::Update(Minion* minion)
{
	minion;
}

void MinionAbsorbState::Exit(Minion* minion)
{
	minion->GetSprite().GetSprite().isActive = true;
	minion->GetCollider().isActive = true;
}

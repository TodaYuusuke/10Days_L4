#include "ColMaskGetter.h"
#include <object/core/collision/CollisionMask.h>

int ColMaskGetter::GetPlayer()
{
	return ColMask0;
}

int ColMaskGetter::GetEnemy()
{
	return ColMask1;
}

int ColMaskGetter::GetWall()
{
	return ColMask2;
}

int ColMaskGetter::GetBullet()
{
	return ColMask3;
}

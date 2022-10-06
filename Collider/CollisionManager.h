#pragma once
#include "Collider.h"
#include "Player.h"
#include "WallManager.h"
#include <vector>

class CollisionManager
{
private:
	bool CheckCrossBoxCollisionPair(Collider* colliderA, Collider* colliderB);
public:
	void CheckAllCollisions(Player* player, WallManager* wall);
};
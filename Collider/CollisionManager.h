#pragma once
#include "Collider.h"
#include "Player.h"
#include "WallManager.h"
#include <vector>

class CollisionManager
{
private:
	bool CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB);
public:
	void CheckAllCollisions(Player* player, WallManager* wallManager);
};
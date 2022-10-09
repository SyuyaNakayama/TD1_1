#pragma once
#include "Collider.h"
#include "player/Player.h"
#include "stage/WallManager.h"
#include <vector>

class CollisionManager
{
private:
	bool CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB);
public:
	void CheckAllCollisions(Player* player, WallManager* wallManager);
};
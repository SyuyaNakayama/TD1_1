#pragma once
#include "Collider.h"
#include "Player.h"
#include "Wall.h"

class CollisionManager
{
private:
	bool CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB);
public:
	void CheckAllCollisions(Player* player, Wall* wall);
};
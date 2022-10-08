#include "CollisionManager.h"
#include "CollisionConfig.h"
#include <list>

using namespace std;

bool CollisionManager::CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB)
{
	if (!(colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask()) ||
		!(colliderB->GetCollisionAttribute() & colliderA->GetCollisionMask()))
	{
		return false;
	}

	Vector3 vecAB = colliderA->GetWorldPosition() - colliderB->GetWorldPosition();
	Vector3 radAB = colliderA->GetRadius() + colliderB->GetRadius();
	vecAB = vecAB.abs();

	return vecAB <= radAB;
}

void CollisionManager::CheckAllCollisions(Player* player, WallManager* wallManager)
{
	list<Collider*> colliders_;

	vector<Wall> walls = wallManager->GetWalls();
	Goal* goal = wallManager->GetGoal();

	colliders_.push_back(player);
	for (Wall& wall : walls) { colliders_.push_back(&wall); }
	colliders_.push_back(goal);

	list<Collider*>::iterator itrA = colliders_.begin();

	Collider* colliderA = *colliders_.begin();
	list<Collider*>::iterator itrB = itrA;
	itrB++;

	for (; itrB != colliders_.end(); ++itrB)
	{
		Collider* colliderB = *itrB;
		if (CheckBoxCollisionPair(colliderA, colliderB))
		{
			colliderA->OnCollision();
			colliderB->OnCollision();
		}
	}
}
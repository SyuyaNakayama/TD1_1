#include "CollisionManager.h"
#include "CollisionConfig.h"
#include <list>
#include <memory>

using namespace std;

bool CollisionManager::CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB)
{
	if (!(colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask()) ||
		!(colliderB->GetCollisionAttribute() & colliderA->GetCollisionMask()))
	{
		return 0;
	}

	Vector3 vecAB = colliderA->GetWorldPosition() - colliderB->GetWorldPosition();
	Vector3 radAB = colliderA->GetRadius() + colliderB->GetRadius();
	vecAB = vecAB.abs();

	if (vecAB <= radAB) { return 1; }

	return 0;
}

void CollisionManager::CheckAllCollisions(Player* player, Wall* wall)
{
	list<Collider*> colliders_;

	list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA)
	{
		Collider* colliderA = *itrA;
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
}
#include "CollisionManager.h"
#include "CollisionConfig.h"
#include <list>

using namespace std;

// 2Dベクトル外積による当たり判定
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

void CollisionManager::CheckAllCollisions(Player* player, WallManager* wall)
{
	list<Collider*> colliders_;
	colliders_.push_back(player);
	vector<Wall> walls = wall->GetWalls();
	for (size_t i = 0; i < walls.size(); i++) { colliders_.push_back(&walls[i]); }

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
#pragma once
#include "Vector3.h"
#include <cstdint>
#include "CollisionConfig.h"

class Collider
{
private:
	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t collisionMask_ = 0xffffffff;
public:
	virtual void OnCollision() = 0;
	const virtual Vector3 GetWorldPosition() = 0;
	const virtual Vector3 GetRadius() = 0;
	uint32_t GetCollisionAttribute() { return collisionAttribute_; }
	uint32_t GetCollisionMask() { return collisionMask_; }
	void SetCollisionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }
	void SetCollisionMask(uint32_t collisionMask) { collisionMask_ = collisionMask; }
};
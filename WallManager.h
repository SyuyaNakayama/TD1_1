#pragma once
#include "Wall.h"
#include <vector>
#include "ViewProjection.h"

class WallManager :Collider
{
private:
	std::vector<Wall> walls_;

public:
	void Initialize();
	void AllDraw(ViewProjection viewProjection);
	std::vector<Wall> GetWalls() { return walls_; }

	void OnCollision() {};
	const Vector3 GetWorldPosition() { return {}; }
	const Vector3 GetRadius() { return {}; }
	const float GetRotateY() { return {}; }
};
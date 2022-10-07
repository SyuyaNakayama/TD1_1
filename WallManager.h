#pragma once
#include "Wall.h"
#include <vector>
#include "ViewProjection.h"
#include "Goal.h"

class WallManager :Collider
{
private:
	std::vector<Wall> walls_;
	Goal goal_;

public:
	void Initialize();
	void AllDraw(ViewProjection viewProjection);

	std::vector<Wall> GetWalls() { return walls_; }
	void SetWalls(UINT32 stage);
	Goal GetGoal() { return goal_; }

	void OnCollision() {};
	const Vector3 GetWorldPosition() { return {}; }
	const Vector3 GetRadius() { return {}; }
};
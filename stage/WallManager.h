#pragma once
#include "Wall.h"
#include <vector>
#include "ViewProjection.h"
#include "Goal.h"
#include <memory>

class WallManager
{
private:
	std::vector<Wall> walls_;
	std::unique_ptr<Goal> goal_;

public:
	void Initialize();
	void AllDraw(ViewProjection viewProjection,int goalRenderTarget);

	std::vector<Wall> GetWalls() { return walls_; }
	void SetStage(UINT32 stage);
	Goal* GetGoal() { return goal_.get(); }
};
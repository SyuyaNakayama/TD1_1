#include "WallManager.h"

void WallManager::Initialize()
{
	SetWalls(1);
	goal_.Initialize();
	goal_.SetGoal(1);
}

void WallManager::AllDraw(ViewProjection viewProjection)
{
	for (size_t i = 0; i < walls_.size(); i++) { walls_[i].Draw(viewProjection); }
	goal_.Draw(viewProjection);
}

void WallManager::SetWalls(UINT32 stage)
{
	if (!walls_.empty()) { walls_.clear(); }
	switch (stage)
	{
	case 1:
		walls_.resize(2);
		walls_[0].Initialize({ -50.0f,0 }, { 20.0f,50.0f });
		walls_[1].Initialize({ 50.0f,0 }, { 20.0f,50.0f });
		break;
	}
}

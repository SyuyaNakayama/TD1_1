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
	walls_.clear();

	switch (stage)
	{
	case 1:
		walls_.resize(4);
		walls_[0].Initialize({ -50.0f,70.0f }, { 20.0f,100.0f });
		walls_[1].Initialize({ +50.0f,70.0f }, { 20.0f,100.0f });
		walls_[2].Initialize({ 0,-50.0f }, { 70.0f,20.0f });
		walls_[3].Initialize({ 0,190.0f }, { 70.0f,20.0f });
		break;
	}
}

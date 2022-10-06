#include "WallManager.h"

void WallManager::Initialize()
{
	walls_.resize(2);
	walls_[0].Initialize({ -50.0f,0 }, { 20.0f,50.0f });
	walls_[1].Initialize({ 50.0f,0 }, { 20.0f,50.0f });
}

void WallManager::AllDraw(ViewProjection viewProjection)
{
	for (size_t i = 0; i < walls_.size(); i++) { walls_[i].Draw(viewProjection); }
}

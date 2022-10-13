#pragma once
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Model.h"
#include "ViewProjection.h"

class Skydome
{
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

public:
	void Initialize();
	void Draw(ViewProjection viewProjection);
};
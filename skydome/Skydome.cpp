#include "Skydome.h"

void Skydome::Initialize()
{
	model_ = Model::CreateFromOBJ("Background",true);
	worldTransform_.scale_ = { 2000.0f,2000.0f,2000.0f };
	worldTransform_.translation_ = {};
	worldTransform_.Initialize();
	worldTransform_.Update();
}

void Skydome::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
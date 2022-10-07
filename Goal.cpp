#include "Goal.h"

void Goal::Initialize()
{
	model_ = Model::Create();
	worldTransform_.scale_ = { 10.0f,Y_RAD ,10.0f };
	worldTransform_.Initialize();
	worldTransform_.Update();
	SetCollisionAttribute(CollisionAttribute::Wall);
	SetCollisionMask(CollisionMask::Wall);
}

void Goal::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

void Goal::SetGoal(int stage)
{
	isGoal = false;

	switch (stage)
	{
	case 1:
		worldTransform_.translation_ = { 30.0f,Y_POS,50.0f };
		break;
	}
	worldTransform_.Update();
}
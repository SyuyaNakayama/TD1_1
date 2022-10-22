#include "Goal.h"

void Goal::Initialize()
{
	model_ = Model::CreateFromOBJ("Goal");
	worldTransform_.scale_ = { 5.0f,5.0f ,5.0f };
	worldTransform_.rotation_ = { 0.0f,3.14f / 2.0f,0.0f };
	worldTransform_.Initialize();
	worldTransform_.Update();
	iconWorldTransform_.scale_ = { 2.5f,2.5f,2.5f };
	iconWorldTransform_.rotation_ = { 0.0f,3.14f / 2.0f,3.14f / 2.0f };
	iconWorldTransform_.Initialize();
	iconWorldTransform_.Update();
	SetCollisionAttribute(CollisionAttribute::Goal);
	SetCollisionMask(CollisionMask::Wall);
}

void Goal::Draw(ViewProjection viewProjection, int renderTarget)
{
	if (renderTarget == 0) { model_->Draw(worldTransform_, viewProjection); }
	if (renderTarget == 1) { model_->Draw(iconWorldTransform_, viewProjection); }
}

void Goal::SetGoal(int stage)
{
	isGoal = false;

	switch (stage)
	{
	case 1:
		worldTransform_.translation_ = { 0,Y_POS,160.0f };
		iconWorldTransform_.translation_ = { 0,Y_POS + 40.0f,160.0f };
		break;
	case 2:
		worldTransform_.translation_ = { 100.0f,Y_POS,-20.0f };
		iconWorldTransform_.translation_ = { 100.0f,Y_POS,-20.0f };
		break;
	case 3:
		worldTransform_.translation_ = { 200.0f,Y_POS,200.0f };
		iconWorldTransform_.translation_ = { 200.0f,Y_POS,200.0f };
		break;
	case 4:
		worldTransform_.translation_ = { 0.0f,Y_POS,360.0f };
		iconWorldTransform_.translation_ = { 0.0f,Y_POS,360.0f };
		break;
	case 5:
		worldTransform_.translation_ = { 240.0f,Y_POS,-240.0f };
		iconWorldTransform_.translation_ = { 240.0f,Y_POS,-240.0f };
		break;
	case 6:
		worldTransform_.translation_ = { -100.0f,Y_POS,120.0f };
		iconWorldTransform_.translation_ = { -100.0f,Y_POS,120.0f };
		break;
	case 7:
		worldTransform_.translation_ = { 400.0f,Y_POS,-300.0f };
		iconWorldTransform_.translation_ = { 400.0f,Y_POS,-300.0f };
		break;
	case 8:
		worldTransform_.translation_ = { 280.0f,Y_POS,-280.0f };
		iconWorldTransform_.translation_ = { 280.0f,Y_POS,-280.0f };
		break;
	}
	worldTransform_.Update();
	iconWorldTransform_.Update();
}
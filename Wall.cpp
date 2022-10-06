#include "Wall.h"

void Wall::Initialize(Vector2 pos, Vector2 radius)
{
	model_ = Model::Create();
	worldTransform_.translation_ = { pos.x,Y_POS_RAD,pos.y };
	worldTransform_.scale_ = { radius.x,Y_POS_RAD,radius.y };
	worldTransform_.Initialize();
	worldTransform_.Update();
	SetCollisionAttribute(CollisionAttribute::Wall);
	SetCollisionMask(CollisionMask::Wall);
}

void Wall::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
#include "Player.h"
#include <DirectXMath.h>
#include "MathUtility.h"

using namespace DirectX;

void Player::Move()
{
	if (!input_->PushKey(DIK_SPACE)) { return; }

	Vector3 moveSpd = Vector3(0, 0, MOVE_SPD) * Matrix4RotationY(worldTransform_.rotation_.y);
	worldTransform_.translation_ += moveSpd;
	viewProjection_->eye += moveSpd;
	viewProjection_->target += moveSpd;
	viewProjection_->UpdateMatrix();
}

void Player::Rotate()
{
	if (input_->PushKey(DIK_SPACE)) { return; }

	worldTransform_.rotation_.y += ROT_SPD;
	if (worldTransform_.rotation_.y >= XM_2PI) { worldTransform_.rotation_.y = 0; }
}

void Player::Initialize(ViewProjection* viewProjection)
{
	model_ = Model::Create();
	input_ = Input::GetInstance();
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	SetCollisionAttribute(CollisionAttribute::Player);
	SetCollisionMask(CollisionMask::Player);
}

void Player::Update()
{
	Rotate();
	Move();
	worldTransform_.Update();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

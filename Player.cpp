#include "Player.h"
#include <DirectXMath.h>
#include "MathUtility.h"

using namespace DirectX;

void Player::Move()
{
	if (!input_->PushKey(DIK_SPACE)) { return; }

	worldTransform_.translation_ += Vector3(0, 0, MOVE_SPD) * Matrix4RotationY(angle_);
}

void Player::Rotate()
{
	if (input_->PushKey(DIK_SPACE)) { return; }

	angle_ += ROT_SPD;
	if (angle_ >= XM_2PI) { angle_ = 0; }
}

void Player::Initialize()
{
	model_ = Model::Create();
	input_ = Input::GetInstance();
	worldTransform_.Initialize();
}

void Player::Update()
{
	Rotate();
	Move();
	worldTransform_.Update();
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

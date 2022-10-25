#include "Player.h"
#include <DirectXMath.h>
#include "MathUtility.h"
#include "GameScene.h"

using namespace DirectX;

void Player::Move()
{
	if (!input_->PushKey(DIK_SPACE)) { return; }

	Vector3 moveSpd = Vector3(0, 0, MOVE_SPD) * Matrix4RotationY(worldTransform_.rotation_.y);
	worldTransform_.translation_ += moveSpd;
	viewProjection_->eye += moveSpd;
	viewProjection_->target += moveSpd;
	viewProjection_->UpdateMatrix();
	mapCamera_->eye += moveSpd;
	mapCamera_->target += moveSpd;
	mapCamera_->UpdateMatrix();
}

void Player::Rotate()
{
	if (input_->PushKey(DIK_SPACE)) { return; }

	worldTransform_.rotation_.y += ROT_SPD;
	if (worldTransform_.rotation_.y >= XM_2PI) { worldTransform_.rotation_.y = 0; }
}

void Player::Initialize(ViewProjection* viewProjection, ViewProjection* mapCamera, uint32_t* stage)
{
	model_ = Model::CreateFromOBJ("player", true);
	input_ = Input::GetInstance();
	viewProjection_ = viewProjection;
	mapCamera_ = mapCamera;
	worldTransform_.scale_ = { 2.0f,2.0f,2.0f };
	worldTransform_.Initialize();
	worldTransform_.Update();
	stage_ = stage;
	SetCollisionAttribute(CollisionAttribute::Player);
	SetCollisionMask(CollisionMask::Player);
	soundManager_ = SoundManager::GetInstance();
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

void Player::OnCollision()
{
	life_--; isDead_ = true;
	soundManager_->PlaySE(SoundManager::Hit);
}

void Player::InitPosAndCamera()
{
	worldTransform_.translation_ = {};
	worldTransform_.Update();
	viewProjection_->eye = { 0,10.0f,-20.0f };
	viewProjection_->target = {};
	viewProjection_->UpdateMatrix();
	mapCamera_->eye = { 0,2000.0f,0 };
	mapCamera_->target = {};
	mapCamera_->UpdateMatrix();
	isDead_ = false;
}
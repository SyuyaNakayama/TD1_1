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
	mapCamera_->eye += moveSpd;
	mapCamera_->target += moveSpd;
	mapCamera_->UpdateMatrix();
}

void Player::Rotate()
{
	if (input_->PushKey(DIK_SPACE)) { return; }

	worldTransform_.rotation_.y += ROT_SPD;
	if (worldTransform_.rotation_.y >= XM_2PI) { worldTransform_.rotation_.y = 0; }
	sprite_->SetRotation(worldTransform_.rotation_.y);
}

void Player::Initialize(ViewProjection* viewProjection, ViewProjection* mapCamera)
{
	model_ = Model::Create();
	input_ = Input::GetInstance();
	mapIconTexture_ = TextureManager::Load("playerMapIcon.png");
	sprite_ = Sprite::Create(mapIconTexture_, { 1180,100 }, { 1,1,1,1 }, { 0.5f,0.75f });
	sprite_->SetSize({ 12,24 });
	viewProjection_ = viewProjection;
	mapCamera_ = mapCamera;
	worldTransform_.scale_ = { 2.0f,2.0f,2.0f };
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

void Player::SpriteDraw()
{
	sprite_->Draw();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

void Player::OnCollision()
{
	life_--;
	worldTransform_.translation_ = {};
	worldTransform_.Update();
	viewProjection_->eye = { 0,10.0f,-20.0f };
	viewProjection_->target = { 0,0,0 };
	mapCamera_->eye = { 0,4000.0f,0 };;
	mapCamera_->target = { 0.01f,0,0 };
}
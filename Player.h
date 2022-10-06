#pragma once
#include "Collider/Collider.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Model.h"
#include "Input.h"
#include "ViewProjection.h"

class Player :public Collider
{
private:
	WorldTransform worldTransform_{};
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	const float MOVE_SPD = 1.0f;
	const float ROT_SPD = 0.03f;
	int life_;
	ViewProjection* viewProjection_;
	ViewProjection* mapCamera_;

	void Move();
	void Rotate();
public:
	void Initialize(ViewProjection* viewProjection,ViewProjection* mapCamera);
	void Update();
	void Draw();
	void Draw(ViewProjection viewProjection);

	void OnCollision() { life_--; }
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
	const float GetRotateY() { return worldTransform_.rotation_.y; }
};
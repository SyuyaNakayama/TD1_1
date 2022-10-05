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
	float angle_ = 0;
	const float MOVE_SPD = 1.0f;
	const float ROT_SPD = 0.01f;
	int life_;

	void Move();
	void Rotate();
public:
	void Initialize();
	void Update();
	void Draw(ViewProjection viewProjection);

	void OnCollision() { life_--; }
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
};
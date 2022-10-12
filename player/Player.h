#pragma once
#include "Collider/Collider.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Model.h"
#include "Input.h"
#include "ViewProjection.h"
#include "Sprite.h"

class Player :public Collider
{
private:
	WorldTransform worldTransform_;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	const float MOVE_SPD = 1.0f;
	const float ROT_SPD = 0.03f;
	const int MAX_LIFE = 3;
	int life_ = MAX_LIFE;
	ViewProjection* viewProjection_ = nullptr;
	ViewProjection* mapCamera_ = nullptr;
	Sprite* sprite_ = nullptr;
	uint32_t texture_ = 0, mapIconTexture_ = 0;
	uint32_t* stage_;

	void Move();
	void Rotate();
public:
	void Initialize(ViewProjection* viewProjection, ViewProjection* mapCamera, uint32_t* stage);
	void Update();
	void SpriteDraw();
	void Draw();

	void Init();
	int GetLife() { return life_; }
	Vector3 GetPosition() { return worldTransform_.translation_; }

	void OnCollision();
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
};
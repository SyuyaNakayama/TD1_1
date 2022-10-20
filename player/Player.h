#pragma once
#include "Collider/Collider.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Model.h"
#include "Input.h"
#include "ViewProjection.h"
#include "Sprite.h"
#include "SoundManager/SoundManager.h"

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
	uint32_t* stage_;
	bool isDead_ = false;
	SoundManager* soundManager_ = nullptr;

	void Move();
	void Rotate();
public:
	void Initialize(ViewProjection* viewProjection, ViewProjection* mapCamera, uint32_t* stage);
	void LifeInit() { life_ = MAX_LIFE; }
	void InitPosAndCamera();
	void Update();
	void Draw();

	int GetLife() { return life_; }
	float GetRotateY() { return worldTransform_.rotation_.y; }
	bool IsDead() { return isDead_; }
	uint32_t GetStage() { return *stage_; }

	void OnCollision();
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_ - Vector3(0.3f, 0.3f, 0.3f); }
};
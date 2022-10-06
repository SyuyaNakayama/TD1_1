#pragma once
#include "Collider/Collider.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Model.h"
#include "ViewProjection.h"

class Wall :public Collider
{
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	const float Y_POS_RAD = -20.0f;
public:
	void Initialize(Vector2 pos, Vector2 radius); // ê›íËílÇÕx,zÇÃÇ›,yílÇÕå≈íË
	void Draw(ViewProjection viewProjection);

	void OnCollision() {};
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
	const float GetRotateY() { return worldTransform_.rotation_.y; }
};
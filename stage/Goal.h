#pragma once
#include "Collider/Collider.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Model.h"
#include "ViewProjection.h"

class Goal :public Collider
{
	WorldTransform worldTransform_,iconWorldTransform_;
	Model* model_ = nullptr;
	const float Y_POS = 5.0f;
	const float Y_RAD = fabs(Y_POS) * 2.0f;
	bool isGoal = 0;
public:
	void Initialize(); // ê›íËílÇÕx,zÇÃÇ›,yílÇÕå≈íË
	void Draw(ViewProjection viewProjection, int renderTarget);
	bool IsGoal() { return isGoal; }

	void SetGoal(int stage);

	void OnCollision() { isGoal = true; }
	const Matrix4 GetWorldMatrix() { return worldTransform_.matWorld_; }
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
};
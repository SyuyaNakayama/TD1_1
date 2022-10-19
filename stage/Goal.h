#pragma once
#include "Collider/Collider.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Model.h"
#include "ViewProjection.h"

class Goal :public Collider
{
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	const float Y_POS = -20.0f;
	const float Y_RAD = fabs(Y_POS) * 2.0f;
	bool isGoal = 0;
public:
	void Initialize(); // 設定値はx,zのみ,y値は固定
	void Draw(ViewProjection viewProjection);
	bool IsGoal() { return isGoal; }

	void SetGoal(int stage);

	void OnCollision() { isGoal = true; }
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
}; 
#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "DebugCamera.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Wall.h"
#include "Collider/CollisionManager.h"
#include <vector>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
  public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	Model* model_;
	ViewProjection viewProjection_;
	CollisionManager collisionManager_;
	Player player_;
	WallManager wallManager_;
	Wall wall_;
};

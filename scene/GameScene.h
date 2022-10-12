#pragma once

#include <vector>
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
#include "player/Player.h"
#include "stage/Wall.h"
#include "Collider/CollisionManager.h"
#include "Fade/Fade.h"
#include "enum.h"
#include "animationManager/AnimationManager.h"

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
	Sprite* uiSprite_ = nullptr;
	std::vector<Sprite*> sceneSprite_;
	std::vector<Sprite*> gameoverSprite_;
	uint32_t uiTexture_ = 0;
	ViewProjection viewProjection_;
	ViewProjection mapCamera_;
	CollisionManager collisionManager_;
	Scene scene_ = Scene::Play;
	Player player_;
	WallManager wallManager_;
	uint32_t stage_ = 1;
	Fade fadeManager_;
	AnimationManager animationManager_;
};

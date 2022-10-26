#pragma once

#include <vector>
#include "Audio.h"
#include "DirectXCommon.h"
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
#include "uiDrawer/UIDrawer.h"
#include "skydome/Skydome.h"
#include "ParticleManager/ParticleManager.h"
#include "SoundManager/SoundManager.h"

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
	void Update_SceneChange();
	void Update_Sound();
	void Update_Play();
	void Update_Animation();

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	std::vector<Sprite*> sceneSprite_;
	ViewProjection viewProjection_;
	ViewProjection mapCamera_;
	uint32_t stage_ = 1;
	Vector2 goalTexturePos_{};
	CollisionManager collisionManager_;
	Scene scene_ = Scene::Title;
	Player player_;
	WallManager wallManager_;
	Fade fadeManager_;
	AnimationManager animationManager_;
	UIDrawer uiDrawer_;
	Skydome background_;
	ParticleManager* particleManager_;
	SoundManager* soundManager_;
};

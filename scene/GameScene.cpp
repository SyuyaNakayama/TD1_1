#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "MathUtility.h"

using namespace std;

void GameScene::Initialize() {
	// 機能の初期化
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	// スプライト生成
	sceneSprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/explanation.png"), {}));
	animationManager_.SetSprite(TextureManager::Load("sceneSprite/title.png"), 2, 20);
	animationManager_.SetSprite(TextureManager::Load("sceneSprite/gameclear.png"), 4, 8);
	animationManager_.SetSprite(TextureManager::Load("sceneSprite/gameover.png"), 7, 8);
	// ビュープロジェクションの初期化
	viewProjection_.eye.z = -20.0f;
	viewProjection_.eye.y = 10.0f;
	viewProjection_.aspectRatio = 3.0f / 2.0f;
	viewProjection_.Initialize();
	viewProjection_.farZ = 4000.0f;
	viewProjection_.UpdateMatrix();
	// マップカメラの初期化
	mapCamera_.eye = { 0,2000.0f,0 };
	mapCamera_.target = { 0,0,0 };
	mapCamera_.aspectRatio = 1.0f;
	mapCamera_.fovAngleY = 3.0f * PI / 180.0f;
	mapCamera_.farZ = 5000.0f;
	mapCamera_.up = { 0,0,1 };
	mapCamera_.Initialize();
	// プレイヤーの初期化
	player_.Initialize(&viewProjection_, &mapCamera_, &stage_);
	// 壁の初期化
	wallManager_.Initialize();
	// フェードマネージャーの初期化
	fadeManager_.Initialize(&scene_);
	// UIドローワーの初期化
	uiDrawer_.Initialize(&player_);
	background_.Initialize();
	particleManager_ = ParticleManager::Create();
}

void GameScene::Update()
{
	switch (scene_)
	{
	case Title:
		animationManager_.Update(0);
		if (input_->PushKey(DIK_SPACE)) { fadeManager_.ChangeScene(HowToPlay); }
		break;
	case HowToPlay:
		if (input_->PushKey(DIK_SPACE)) { fadeManager_.ChangeScene(Play); }
		break;
	case Play:
		if (!fadeManager_.IsFade()) { player_.Update(); }

		if (input_->PushKey(DIK_SPACE) && !fadeManager_.IsFade())
		{
			// 当たり判定
			collisionManager_.CheckAllCollisions(&player_, &wallManager_);
		}

		// ゴール
		if (wallManager_.GetGoal()->IsGoal())
		{
			if (stage_ <= 7)
			{
				// 次のステージ
				fadeManager_.FadeScene();
				if (fadeManager_.IsChange())
				{
					wallManager_.SetStage(++stage_);
					player_.LifeInit();
					player_.InitPosAndCamera();
				}
			}
			else
			{
				fadeManager_.ChangeScene(Clear);
			}
		}
		// ミス
		if (player_.IsDead())
		{
			if (player_.GetLife() > 0)
			{
				// リトライ
				fadeManager_.FadeScene();
				if (fadeManager_.IsChange()) { player_.InitPosAndCamera(); }
			}
			else
			{
				// ゲームオーバー
				fadeManager_.ChangeScene(GameOver);
			}

			if (fadeManager_.GetAlpha() <= 0.25) { particleManager_->Add(60, 1.0f, 0.0f); }
		}

		uiDrawer_.Update(wallManager_.GetGoal()->GetWorldPosition());

		particleManager_->Update();
		break;
	case Clear:
		animationManager_.Update(1);
		if (input_->PushKey(DIK_SPACE))
		{
			fadeManager_.ChangeScene(Title);
			player_.LifeInit();
			player_.InitPosAndCamera();
			wallManager_.SetStage(stage_ = 1);
		}
		break;
	case GameOver:
		animationManager_.Update(2);
		if (input_->PushKey(DIK_SPACE))
		{
			fadeManager_.ChangeScene(Play);
			player_.LifeInit();
			player_.InitPosAndCamera();
			if (stage_ <= 4) { wallManager_.SetStage(stage_ = 1); }
			else { wallManager_.SetStage(stage_ = 5); }
		}
		break;
	}

	fadeManager_.Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	dxCommon_->SetViewport({}, { WinApp::kWindowWidth,WinApp::kWindowHeight }); // ビューポート切り替え

	switch (scene_)
	{
	case Title:
		animationManager_.Draw(0);
		break;
	case HowToPlay:
		sceneSprite_[0]->Draw();
		break;
	case Play:
		break;
	case Clear:
		animationManager_.Draw(1);
		break;
	case GameOver:
		animationManager_.Draw(2);
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion
#pragma region 3Dオブジェクト描画
	if (scene_ == Play)
	{
		Model::PreDraw(commandList);
		// 3Dオブジェクト描画前処理
		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// </summary>
		dxCommon_->SetViewport({}, { WinApp::kWindowWidth - 200, WinApp::kWindowHeight }); // ビューポート切り替え
		wallManager_.AllDraw(viewProjection_);
		if (!player_.IsDead()) { player_.Draw(); }
		background_.Draw(viewProjection_);

		dxCommon_->SetViewport({ WinApp::kWindowWidth - 200, 0.0f }, { 200.0f, 200.0f }); // ビューポート切り替え
		wallManager_.AllDraw(mapCamera_);
		background_.Draw(mapCamera_);
		// 3Dオブジェクト描画後処理
		Model::PostDraw();
		dxCommon_->SetViewport({}, { WinApp::kWindowWidth - 200, WinApp::kWindowHeight }); // ビューポート切り替え
		ParticleManager::PreDraw(commandList);
		particleManager_->Draw();
		ParticleManager::PostDraw();
	}
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	dxCommon_->SetViewport({ 0,0 }, { 1280.0f,720.0f });
	if (scene_ == Play)
	{
		uiDrawer_.Draw();
	}
	fadeManager_.Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

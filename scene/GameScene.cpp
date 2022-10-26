#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace std;

void GameScene::Initialize() {
	// 機能の初期化
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	// スプライト生成
	sceneSprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/explanation.png"), {}));
	sceneSprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/spaceletter.png"), {}));
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
	soundManager_ = SoundManager::GetInstance();
	soundManager_->PlayBGM(SoundManager::Title);
}

void GameScene::Update()
{
	Update_Animation();
	Update_SceneChange();
	fadeManager_.Update();
	Update_Sound();
	Update_Play();
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
		sceneSprite_[1]->Draw();
		break;
	case Clear:
		animationManager_.Draw(1);
		sceneSprite_[1]->Draw();
		break;
	case GameOver:
		animationManager_.Draw(2);
		sceneSprite_[1]->Draw();
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
		wallManager_.AllDraw(viewProjection_, 0);
		if (!player_.IsDead()) { player_.Draw(); }
		background_.Draw(viewProjection_);

		dxCommon_->SetViewport({ WinApp::kWindowWidth - 200, 0.0f }, { 200.0f, 200.0f }); // ビューポート切り替え
		wallManager_.AllDraw(mapCamera_, 1);
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

void GameScene::Update_SceneChange()
{
	if (!input_->PushKey(DIK_SPACE)) { return; }
	switch (scene_)
	{
	case Title:
		fadeManager_.ChangeScene(HowToPlay);
		sceneSprite_[1]->SetPosition({ 1000.0f,600.0f });
		break;
	case HowToPlay:
		fadeManager_.ChangeScene(Play);
		break;
	case Clear:
		fadeManager_.ChangeScene(Title);
		player_.LifeInit();
		player_.InitPosAndCamera();
		wallManager_.SetStage(stage_ = 1);
		particleManager_->Clear();
		player_.ResetRotateY();
		break;
	case GameOver:
		fadeManager_.ChangeScene(Play);
		player_.LifeInit();
		player_.InitPosAndCamera();
		particleManager_->Clear();
		player_.ResetRotateY();
		if (stage_ <= 4) { wallManager_.SetStage(stage_ = 1); }
		else { wallManager_.SetStage(stage_ = 5); }
		break;
	}
}

void GameScene::Update_Sound()
{
	if (!fadeManager_.IsChange()) { return; }
	switch (scene_)
	{
	case Title:
		soundManager_->StopBGM(SoundManager::Clear);
		soundManager_->PlayBGM(SoundManager::Title);
		break;
	case Play:
		soundManager_->StopBGM(SoundManager::GameOver);
		soundManager_->StopBGM(SoundManager::Title);
		soundManager_->PlayBGM(SoundManager::Play);
		break;
	case Clear:
		soundManager_->StopBGM(SoundManager::Play);
		soundManager_->PlayBGM(SoundManager::Clear);
		break;
	case GameOver:
		soundManager_->StopBGM(SoundManager::Play);
		soundManager_->PlayBGM(SoundManager::GameOver);
		break;
	}
}

void GameScene::Update_Play()
{
	if (scene_ != Play) { return; }

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
				player_.ResetRotateY();
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
			if (fadeManager_.IsChange()) 
			{ 
				player_.InitPosAndCamera(); 
				player_.ResetRotateY();
			}
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
}

void GameScene::Update_Animation()
{
	switch (scene_)
	{
	case Title:		animationManager_.Update(0); break;
	case Clear:		animationManager_.Update(1); break;
	case GameOver:	animationManager_.Update(2); break;
	}
}
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
	debugCamera_ = new DebugCamera({ WinApp::kWindowWidth,WinApp::kWindowHeight });
	model_ = Model::Create();
	// スプライト生成
	sceneSprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/explanation.png"), {}));
	for (size_t i = 0; i < 7; i++)
	{
		gameoverSprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/gameover.png"), {}));
		gameoverSprite_[i]->SetTextureRect({ WinApp::kWindowWidth * (float)i,0 }, { 1280 * 7,720 });
	}

	animationManager_.SetSprite(gameoverSprite_, 8);

	uiTexture_ = TextureManager::Load("white1x1.png");
	uiSprite_ = Sprite::Create(uiTexture_, { 1080.0f,200.0f }, { 0,0,0,1 });
	uiSprite_->SetSize({ 200,WinApp::kWindowHeight - 200 });
	// ビュープロジェクションの初期化
	viewProjection_.eye.z = -20.0f;
	viewProjection_.eye.y = 10.0f;
	viewProjection_.aspectRatio = 3.0f / 2.0f;
	viewProjection_.Initialize();
	// マップカメラの初期化
	mapCamera_.eye = { 0,4000.0f,0 };
	mapCamera_.target.x = 0.01f;
	mapCamera_.aspectRatio = 1.0f;
	mapCamera_.fovAngleY = 3.0f * PI / 180.0f;
	mapCamera_.farZ = 4500.0f;
	mapCamera_.up = { 0,0,1 };
	mapCamera_.Initialize();
	// プレイヤーの初期化
	player_.Initialize(&viewProjection_, &mapCamera_);
	// 壁の初期化
	wallManager_.Initialize();
	// フェードマネージャーの初期化
	fadeManager_.Initialize(&scene_);
}

void GameScene::Update()
{
	if (input_->TriggerKey(DIK_0)) { fadeManager_.ChangeScene(GameOver); }
	switch (scene_)
	{
	case Title:
		break;
	case HowToPlay:
		break;
	case Play:
		player_.Update();
		collisionManager_.CheckAllCollisions(&player_, &wallManager_);
		debugCamera_->Update();

		if (wallManager_.GetGoal()->IsGoal())
		{
			wallManager_.SetStage(++stage_);
			player_.LifeInit();
		}

		break;
	case Clear:
		break;
	case GameOver:
		animationManager_.Update(0);
		break;
	}

	fadeManager_.Update();
	//debugText_->SetPos(0, 0);
	//debugText_->Printf("stage_:%u", stage_);
	//debugText_->SetPos(0, 20);
	//debugText_->Printf("life:%d", player_.GetLife());
	//viewProjection_ = debugCamera_->GetViewProjection();
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

	static int animeNum = 0;

	switch (scene_)
	{
	case Title:
		break;
	case HowToPlay:
		break;
	case Play:
		uiSprite_->Draw();
		break;
	case Clear:
		break;
	case GameOver:
		animationManager_.Draw(0);
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
		// 3Dオブジェクト描画前処理
		Model::PreDraw(commandList);
		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// </summary>
		dxCommon_->SetViewport({}, { WinApp::kWindowWidth - 200, WinApp::kWindowHeight }); // ビューポート切り替え
		wallManager_.AllDraw(viewProjection_);
		player_.Draw();

		dxCommon_->SetViewport({ WinApp::kWindowWidth - 200, 0.0f }, { 200.0f, 200.0f }); // ビューポート切り替え
		wallManager_.AllDraw(mapCamera_);
		player_.Draw(mapCamera_);
		// 3Dオブジェクト描画後処理
		Model::PostDraw();
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
		player_.SpriteDraw();
	}
	fadeManager_.Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

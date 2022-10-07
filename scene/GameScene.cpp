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
	// ビュープロジェクションの初期化
	viewProjection_.eye.z = -20.0f;
	viewProjection_.eye.y = 10.0f;
	viewProjection_.aspectRatio = 3.0f / 2.0f;
	viewProjection_.Initialize();

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
}

void GameScene::Update()
{
	player_.Update();
	collisionManager_.CheckAllCollisions(&player_, &wallManager_);
	debugCamera_->Update();
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

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion
#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	wallManager_.AllDraw(viewProjection_);
	player_.Draw();

	dxCommon_->SetViewport({ 1080.0f, 0.0f }, { 200.0f, 200.0f }); // ビューポート切り替え

	wallManager_.AllDraw(mapCamera_);
	player_.Draw(mapCamera_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	dxCommon_->SetViewport({ 0,0 }, { 1280.0f,720.0f });
	player_.SpriteDraw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

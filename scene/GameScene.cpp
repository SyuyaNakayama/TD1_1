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
	viewProjection_.Initialize();
	// プレイヤーの初期化
	player_.Initialize(&viewProjection_);
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

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

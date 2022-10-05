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
	viewProjection_.Initialize();
	viewProjection_.eye.z = -10.0f;
	// プレイヤーの初期化
	player_.Initialize();
	// 壁の初期化
	walls.resize(2);
	walls[0].translation_ = { -50.0f,-25.0f,0 };
	walls[1].translation_ = { 50.0f,-25.0f,0 };
	for (size_t i = 0; i < walls.size(); i++)
	{
		walls[i].Initialize();
		walls[i].scale_ = { 20.0f,50.0f,50.0f };
		walls[i].Update();
	}
}

void GameScene::Update()
{
	player_.Update();
	debugCamera_->Update();
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
	for (size_t i = 0; i < walls.size(); i++)
	{
		model_->Draw(walls[i], debugCamera_->GetViewProjection());
	}
	player_.Draw(debugCamera_->GetViewProjection());

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

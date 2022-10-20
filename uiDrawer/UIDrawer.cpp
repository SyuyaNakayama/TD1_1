#include "UIDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"
#include <cmath>

void UIDrawer::Initialize(Player* player)
{
	player_ = player;

	sprites_.push_back(Sprite::Create(TextureManager::Load("white1x1.png"), { 1080.0f,200.0f }, { 0,0,0,1 }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLetter.png"), { 1124.0f,250.0f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerMapIcon.png"), { 1180,100 }, { 1,1,1,1 }, { 0.5f,0.75f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/GoalDirectionArrow.png"), { 1180,100 }, { 1,1,1,1 }, { 0.5f,1.0f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/StageLetter.png"), { 1100,420 }));
	sprites_[0]->SetSize({ 200,WinApp::kWindowHeight - 200 });
	sprites_[2]->SetSize({ 12,24 });
	sprites_[4]->SetSize({ 160,64 });

	for (float i = 0; i < 3; i++)
	{
		playerLife_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLife.png"), { 1095.0f + 60.0f * i,334.0f }));
		playerLife_[i]->SetSize({ 50.0f,50.0f });
	}

	for (size_t i = 0; i < 9; i++)
	{
		stages_.push_back(Sprite::Create(TextureManager::Load("ui/StageNumber.png"), { 1130,504.0f }));
		stages_[i]->SetTextureRect({ 16.0f * (float)i,0 }, { 16.0f,32.0f });
		stages_[i]->SetSize({ 32.0f,64.0f });
	}
	stages_[8]->SetPosition({ 1162.0f,504.0f });
	stages_.push_back(Sprite::Create(TextureManager::Load("ui/StageNumber.png"), { 1194.0f,520.0f }));
	stages_[9]->SetTextureRect({ 16.0f * 7.0f,0 }, { 16.0f,32.0f });
	stages_[9]->SetSize({ 24.0f,48.0f });
}

void UIDrawer::Update(Vector3 goalPosition)
{
	sprites_[2]->SetRotation(player_->GetRotateY());
	Vector3 dirPtoG = goalPosition - player_->GetWorldPosition();
	dirPtoG.normalize();
	sprites_[3]->SetRotation(std::atan2f(dirPtoG.x, dirPtoG.z));
}

void UIDrawer::Draw()
{
	for (Sprite* sprite : sprites_) { sprite->Draw(); }
	for (size_t i = 0; i < player_->GetLife(); i++) { playerLife_[i]->Draw(); }
	stages_[player_->GetStage() - 1]->Draw();
	stages_[8]->Draw();
	stages_[9]->Draw();
}
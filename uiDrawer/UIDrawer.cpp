#include "UIDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"
#include <cmath>

void UIDrawer::Initialize(Player* player)
{
	player_ = player;

	sprites_.push_back(Sprite::Create(TextureManager::Load("white1x1.png"), { 1080.0f,200.0f }, { 0,0,0,1 }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLetter.png"), { 1100.0f,250.0f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/playerMapIcon.png"), { 1180,100 }, { 1,1,1,1 }, { 0.5f,0.75f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/goalDirectionArrow.png"), { 1180,100 }, { 1,1,1,1 }, { 0.5f,1.0f }));
	for (float i = 0; i < 3; i++)
	{
		sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLife.png"), { 1090.0f + 60.0f * i,334.0f }));
		sprites_[4 + i]->SetSize({ 50.0f,50.0f });
	}

	sprites_[0]->SetSize({ 200,WinApp::kWindowHeight - 200 });
	sprites_[2]->SetSize({ 12,24 });
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
	for (int i = 0; i < 4 + player_->GetLife(); i++) { sprites_[i]->Draw(); }
}
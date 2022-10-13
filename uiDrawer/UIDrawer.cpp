#include "UIDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

void UIDrawer::Initialize(Player* player)
{
	player_ = player;

	uint32_t lifeTexture = TextureManager::Load("ui/PlayerLife.png");

	sprites_.push_back(Sprite::Create(TextureManager::Load("white1x1.png"), { 1080.0f,200.0f }, { 0,0,0,1 }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLetter.png"), { 1100.0f,250.0f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/playerMapIcon.png"), { 1180,100 }, { 1,1,1,1 }, { 0.5f,0.75f }));
	sprites_.push_back(Sprite::Create(lifeTexture, { 1090.0f,334.0f }));
	sprites_.push_back(Sprite::Create(lifeTexture, { 1150.0f,334.0f }));
	sprites_.push_back(Sprite::Create(lifeTexture, { 1210.0f,334.0f }));

	sprites_[0]->SetSize({ 200,WinApp::kWindowHeight - 200 });
	sprites_[2]->SetSize({ 12,24 });
	for (size_t i = 0; i < 3; i++) { sprites_[3 + i]->SetSize({ 50.0f,50.0f }); }
}

void UIDrawer::Update()
{
	sprites_[2]->SetRotation(player_->GetRotateY());
}

void UIDrawer::Draw()
{
	for (size_t i = 0; i < 3 + player_->GetLife(); i++) { sprites_[i]->Draw(); }
}
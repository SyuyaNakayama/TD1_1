#include "UIDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

void UIDrawer::Initialize(Player* player)
{
	player_ = player;

	sprites_.push_back(Sprite::Create(TextureManager::Load("white1x1.png"), { 1080.0f,200.0f }, { 0,0,0,1 }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLetter.png"), { 1100.0f,250.0f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLife.png"), { 1090.0f,334.0f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLife.png"), { 1150.0f,334.0f }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLife.png"), { 1210.0f,334.0f }));

	sprites_[0]->SetSize({ 200,WinApp::kWindowHeight - 200 });
	for (size_t i = 0; i < 3; i++) { sprites_[2 + i]->SetSize({ 50.0f,50.0f }); }

}

void UIDrawer::Update()
{
}

void UIDrawer::Draw()
{
	for (size_t i = 0; i < 2 + player_->GetLife(); i++) { sprites_[i]->Draw(); }
}
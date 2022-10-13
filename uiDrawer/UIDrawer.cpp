#include "UIDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

void UIDrawer::Initialize()
{
	sprites_.push_back(Sprite::Create(TextureManager::Load("white1x1.png"), { 1080.0f,200.0f }, { 0,0,0,1 }));
	sprites_.push_back(Sprite::Create(TextureManager::Load("ui/PlayerLetter.png"), { 1100.0f,250 }));
	
	sprites_[0]->SetSize({ 200,WinApp::kWindowHeight - 200 });
}

void UIDrawer::Update()
{
}

void UIDrawer::Draw()
{
	for (Sprite* sprite : sprites_) { sprite->Draw(); }
}
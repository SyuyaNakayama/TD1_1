#include "Fade/Fade.h"
#include "TextureManager.h"
#include "WinApp.h"

void Fade::Initialize()
{
	texture_ = TextureManager::Load("white1x1.png");
	sprite_ = Sprite::Create(texture_, {}, {});
	sprite_->SetSize({ WinApp::kWindowWidth,WinApp::kWindowHeight });
}

void Fade::Update()
{
	alpha += fadePerFlame;
	if (alpha > 1.0f) 
	{
		alpha = 1.0f;
		fadePerFlame = -fadePerFlame;
	}
	if (alpha < 0)
	{
		alpha = 0;
		fadePerFlame = -fadePerFlame;
	}
	sprite_->SetColor({ 0,0,0,alpha });
}

void Fade::Draw()
{
	sprite_->Draw();
}
#include "Fade.h"
#include "TextureManager.h"
#include "WinApp.h"

void Fade::Initialize(Scene* nowScene)
{
	texture_ = TextureManager::Load("white1x1.png");
	sprite_ = Sprite::Create(texture_, {}, {});
	sprite_->SetSize({ WinApp::kWindowWidth,WinApp::kWindowHeight });
	nowScene_ = nowScene;
}

void Fade::Update()
{
	if (!isFade_) { return; }

	alpha_ += fadePerFlame;
	if (alpha_ >= 1.0f)
	{
		alpha_ = 1.0f;
		fadePerFlame = -fadePerFlame;
		*nowScene_ = nextScene_;
	}
	if (alpha_ <= 0)
	{
		alpha_ = 0;
		fadePerFlame = -fadePerFlame;
		isFade_ = false;
	}
	sprite_->SetColor({ 0,0,0,alpha_ });
}

void Fade::Draw()
{
	sprite_->Draw();
}

void Fade::FadeScene()
{
	isFade_ = true;
	nextScene_ = *nowScene_;
}

void Fade::ChangeScene(Scene nextScene)
{
	isFade_ = true;
	nextScene_ = nextScene;
}
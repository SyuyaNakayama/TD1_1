#include "Fade.h"
#include "TextureManager.h"
#include "WinApp.h"

/// <summary>
/// èâä˙âª
/// </summary>
/// <param name="nowScene"></param>
void Fade::Initialize(Scene* nowScene)
{
	texture_ = TextureManager::Load("white1x1.png");
	sprite_ = Sprite::Create(texture_, {}, {});
	sprite_->SetSize({ WinApp::kWindowWidth,WinApp::kWindowHeight });
	nowScene_ = nowScene;
}

void Fade::Update()
{
	isChange_ = false;
	if (!isFade_) { return; }

	alpha_ += fadePerFlame;
	if (alpha_ >= 1.0f)
	{
		isChange_ = true; 
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
	if (isFade_) { return; }
	isFade_ = true;
	nextScene_ = *nowScene_;
}

void Fade::ChangeScene(Scene nextScene)
{
	if (isFade_) { return; }
	isFade_ = true;
	nextScene_ = nextScene;
}
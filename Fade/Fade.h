#pragma once
#include "Sprite.h"

class Fade
{
private:
	const int FADE_TIME = 60;
	float fadePerFlame = 1.0f / FADE_TIME;
	Sprite* sprite_ = nullptr;
	uint32_t texture_ = 0;
	bool isFade_ = 0;
	float alpha = 0;

public:
	void Initialize();
	void Update();
	void Draw();
};
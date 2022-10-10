#include "AnimationManager.h"

void AnimationManager::SetSprite(std::vector<Sprite*> sprite, int frameTime)
{
	sprite_.push_back(sprite);
	timer_.push_back(frameTime);
	frame_.push_back(0);
}

void AnimationManager::Update(int index)
{
	if (!timer_[index].CountDown()) { return; }
	frame_[index]++;
	if (frame_[index] != sprite_[index].size()) { return; }
	frame_[index] = 0;
}

void AnimationManager::Draw(int index)
{
	sprite_[index][frame_[index]]->Draw();
}
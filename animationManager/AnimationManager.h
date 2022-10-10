#pragma once
#include "Sprite.h"
#include "timer/Timer.h"
#include <vector>

class AnimationManager
{
private:
	std::vector<std::vector<Sprite*>> sprite_;
	std::vector<Timer> timer_;
	std::vector<int> frame_;
public:
	void SetSprite(std::vector<Sprite*> sprite,int frameTime);
	void Update(int index);
	void Draw(int index);
};
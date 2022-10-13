#pragma once
#include "Sprite.h"
#include <vector>

class UIDrawer
{
private:
	std::vector<Sprite*> sprites_;
public:
	void Initialize();
	void Update();
	void Draw();
};
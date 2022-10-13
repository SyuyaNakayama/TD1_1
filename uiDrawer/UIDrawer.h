#pragma once
#include "Sprite.h"
#include <vector>
#include "player/Player.h"

class UIDrawer
{
private:
	std::vector<Sprite*> sprites_;
	Player* player_ = nullptr;
public:
	void Initialize(Player* player);
	void Update();
	void Draw();
};
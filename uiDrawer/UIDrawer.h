#pragma once
#include "Sprite.h"
#include <vector>
#include "player/Player.h"

class UIDrawer
{
private:
	std::vector<Sprite*> sprites_,playerLife_,stages_;
	Player* player_ = nullptr;
public:
	void Initialize(Player* player);
	void Update(Vector3 goalPosition);
	void Draw();
};
#pragma once
#include "Audio.h"
#include <vector>

class SoundManager
{
private:
	Audio* audio_;
	std::vector<uint32_t>bgm_, se_;
public:
	void Initialize();
	void PlayBGM(size_t index);
	void PlaySE(size_t index);
	void StopBGM(size_t index);
};
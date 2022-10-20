#pragma once
#include "Audio.h"
#include <vector>

class SoundManager
{
private:
	Audio* audio_;
	std::vector<uint32_t>bgm_, se_;
public:
	enum SoundIndex { Title, Play, Clear, GameOver };

	void Initialize();
	void PlayBGM(SoundIndex index);
	void PlaySE(SoundIndex index);
	void StopBGM(SoundIndex index);
};
#include "SoundManager.h"

void SoundManager::Initialize()
{
	audio_ = Audio::GetInstance();
	//bgm_.push_back(audio_->LoadWave("bgm/"));
	//se_.push_back(audio_->LoadWave("se/"));
}

void SoundManager::PlayBGM(size_t index)
{
	audio_->PlayWave(bgm_[index]);
}

void SoundManager::PlaySE(size_t index)
{
	audio_->PlayWave(se_[index]);
}

void SoundManager::StopBGM(size_t index)
{
	audio_->StopWave(bgm_[index]);
}
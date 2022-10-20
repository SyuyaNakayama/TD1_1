#include "SoundManager.h"

void SoundManager::Initialize()
{
	audio_ = Audio::GetInstance();
	bgm_.push_back(audio_->LoadWave("sound/GameTitle.mp3"));
	bgm_.push_back(audio_->LoadWave("sound/GamePlay.mp3"));
	bgm_.push_back(audio_->LoadWave("sound/GameClear.mp3"));
	bgm_.push_back(audio_->LoadWave("sound/GameOver.mp3"));
	se_.push_back(audio_->LoadWave("sound/PlayerHitSE.mp3"));
}

void SoundManager::PlayBGM(SoundIndex index)
{
	audio_->PlayWave(bgm_[index]);
}

void SoundManager::PlaySE(SoundIndex index)
{
	audio_->PlayWave(se_[index]);
}

void SoundManager::StopBGM(SoundIndex index)
{
	audio_->StopWave(bgm_[index]);
}
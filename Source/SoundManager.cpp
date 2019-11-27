#include "SoundManager.h"

std::map<string, Sound*> SoundManager::soundMap;

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
}

void SoundManager::LoadSounds()
{
	soundMap["doorUnlocked"] = Sound::Load("Sound/Custom/door_unlocked.wav");
	soundMap["doorLocked"] = Sound::Load("Sound/Custom/door_locked.wav");
	soundMap["pickup"] = Sound::Load("Sound/Custom/pickup.wav");
	soundMap["roll"] = Sound::Load("Sound/Custom/roll.wav");
	soundMap["teleport"] = Sound::Load("Sound/Custom/teleport.wav");
	soundMap["win"] = Sound::Load("Sound/Custom/win.wav");
}

void SoundManager::Play(string key)
{
	Sound* sound = soundMap[key];
	if (sound)
	{
		sound->Play();
	}
}

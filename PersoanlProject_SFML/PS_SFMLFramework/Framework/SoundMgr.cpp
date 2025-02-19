#include "stdafx.h"
#include "SoundMgr.h"

void SoundMgr::Init(int totalChannels)
{
	for (int i = 0; i < totalChannels; i++)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundMgr::Release()
{
	for (auto wSound : waiting)
	{
		delete wSound;
	}
	playing.clear();

	for (auto pSound : playing)
	{
		delete pSound;
	}
	waiting.clear();
}

void SoundMgr::Update(float dt)
{
	auto it = playing.begin();
	while (it != playing.end())
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			waiting.push_back(*it);
			playing.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void SoundMgr::PlayBgm(std::string id, bool loop)
{
	PlayBgm(SOUNDBUFFER_MGR.Get(id), loop);
}

void SoundMgr::PlayBgm(sf::SoundBuffer& buffer, bool loop)
{
	bgm.stop();
	bgm.setVolume(bgmVolume);
	bgm.setLoop(loop);
	bgm.setBuffer(buffer);
	bgm.play();
}

void SoundMgr::StopBgm()
{
	bgm.stop();
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(SOUNDBUFFER_MGR.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;

	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}

	sound->setVolume(sfxVolume);
	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->play();
	playing.push_back(sound);
}




void SoundMgr::StopAllSfx()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}

void SoundMgr::SetSfxVolume(float volume)
{

}
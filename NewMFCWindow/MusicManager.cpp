#include "MusicManager.h"

#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>

#pragma comment(lib,"WINMM.LIB")

MusicManager::MusicManager()
= default;


MusicManager& MusicManager::getInstance()
{
	static MusicManager instance;
	return instance;
}

MusicManager::~MusicManager()
= default;

void MusicManager::setWND(HWND hWnd)
{
	lmciMidiHWnd = hWnd;
}

void MusicManager::playBackGroundMusic(const std::string& path) const
{
	char buffer[256];
	sprintf_s(buffer, "open \"%s\" type sequencer alias MUSIC", path.c_str());

	mciSendString("close all", nullptr, 0, nullptr);
	mciSendString(buffer, nullptr, 0, nullptr);
	mciSendString("play MUSIC from 0 notify", nullptr, 0, lmciMidiHWnd);

}

void MusicManager::stopMusic()
{
	mciSendString("close all", nullptr, 0, nullptr);
}

void MusicManager::musicResume() const
{
	mciSendString("play MUSIC notify", nullptr, 0, lmciMidiHWnd);
}


int MusicManager::getMusicState()
{
	char buffer[256];
	mciSendString("status MUSIC mode", buffer, 24, nullptr);
	if (strcmp(buffer, "not ready") == 0)   return MUSIC_STATE_NOT_READY;
	if (strcmp(buffer, "playing") == 0)   return MUSIC_STATE_PLAYING;
	if (strcmp(buffer, "stopped") == 0)   return MUSIC_STATE_STOPPED;
	return MUSIC_STATE_STOPPED;
}

void MusicManager::playDieSound()
{
	sndPlaySound("res/music/explosion.wav", SND_ASYNC | SND_FILENAME);
}

void MusicManager::playUpgradeSound()
{
	sndPlaySound("res/music/ShotCharging.wav", SND_ASYNC | SND_FILENAME);
}


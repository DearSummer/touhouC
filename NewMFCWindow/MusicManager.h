#pragma once
#include <string>
#include <windows.h>

#define MUSIC_STATE_PLAYING 1
#define MUSIC_STATE_NOT_READY -1
#define MUSIC_STATE_STOPPED 0

class MusicManager
{
	MusicManager();

	HWND lmciMidiHWnd;

public:
	static MusicManager& getInstance();
	~MusicManager();

	void setWND(HWND hWnd);
	void playBackGroundMusic(const std::string& path) const;
	void musicResume() const;
	static void stopMusic();
	static int getMusicState();
	static void playDieSound();
	static void playUpgradeSound();
};


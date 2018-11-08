#pragma once
#include "IGameLoop.h"
#include "Character.h"
#include "Animation.h"
#include "Iku.h"

class BaseGameLoop : public IGameLoop
{

	Sprite * menu;
	Sprite * startGame;
	Sprite * music;

	std::string musicString[21];
	int musicIndex;

	bool playMusic;
	void _initMusic();
	void _playMusic();
public:
	BaseGameLoop();
	~BaseGameLoop();

	void onStart() override;
	void update(CDC* dc, CDC* canvasDC) override;
};


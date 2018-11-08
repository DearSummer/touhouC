#include "BaseGameLoop.h"
#include "Time.h"
#include "BulletManager.h"
#include "InputSignal.h"
#include "EnemyManager.h"
#include "GameManager.h"
#include "BuffManager.h"
#include "Util.h"
#include "Input.h"
#include "MusicManager.h"


void BaseGameLoop::_initMusic()
{
	musicString[0].assign("01. ÓÀÒ¹³­¡¡¡« Eastern Night");
	musicString[1].assign("02. »ÃÒ•¤ÎÒ¹¡¡¡« Ghostly Eyes");
	musicString[2].assign("03. ´À¡©ÇïÔÂ¡¡¡« Mooned Insect");
	musicString[3].assign("04. Ò¹È¸¤Î¸èÉù¡¡¡« Night Bird");
	musicString[4].assign("05. ¤â¤¦¸è¤·¤«Â„¤³¤¨¤Ê¤¤");
	musicString[5].assign("06. ‘¯¤«¤·¤­–|·½¤ÎÑª¡¡¡« Old World");
	musicString[6].assign("07. ¥×¥ì¥¤¥ó¥¨¥¤¥¸¥¢");
	musicString[7].assign("08. ÓÀÒ¹¤Îˆó¤¤¡¡¡« Imperishable Night");
	musicString[8].assign("09. ÉÙÅ®¾_ÏëÇú¡¡¡« Dream Battle");
	musicString[9].assign("10. ÁµÉ«¥Þ¥¹¥¿©`¥¹¥Ñ©`¥¯");
	musicString[10].assign("11. ¥·¥ó¥Ç¥ì¥é¥±©`¥¸¡¡¡« Kagome-Kagome");
	musicString[11].assign("12. ¿ñšÝ¤ÎÍ«¡¡¡« Invisible Full Moon");
	musicString[12].assign("13. ¥ô¥©¥ä©`¥¸¥å1969");
	musicString[13].assign("14. Ç§Äê»ÃÏëà_¡¡¡« History of the Moon");
	musicString[14].assign("15. ÖñÈ¡ïwÏè¡¡¡« Lunatic Princess");
	musicString[15].assign("16. ¥ô¥©¥ä©`¥¸¥å1970");
	musicString[16].assign("17. ¥¨¥¯¥¹¥Æ¥ó¥É¥¢¥Ã¥·¥å¡¡¡« ÅîÀ³ÈË");
	musicString[17].assign("18. ÔÂ¤Þ¤Ç½ì¤±¡¢²»ËÀ¤ÎŸŸ");
	musicString[18].assign("19. ÔÂÒŠ²Ý");
	musicString[19].assign("20. Eternal Dream¡¡¡« ÓÄÐþ¤ÎéÊ˜ä");
	musicString[20].assign("21. –|·½Ñý¹ÖÐ¡î®");
}

void BaseGameLoop::_playMusic()
{
	char buffer[256] = { 0 };
	sprintf_s(buffer, "res/music/%s.mid", musicString[musicIndex].c_str());

	MusicManager::getInstance().playBackGroundMusic(buffer);
	musicIndex++;
	musicIndex %= 21;
}

BaseGameLoop::BaseGameLoop():musicIndex(0),playMusic(true)
{
	menu = new Sprite("res/back.bmp", 658, 658);
	startGame = new Sprite("res/start_game.bmp", 300, 71);
	music = new Sprite("res/music.bmp", 300, 77);

	_initMusic();
}


BaseGameLoop::~BaseGameLoop()
{
}

void BaseGameLoop::onStart()
{	
	_playMusic();

	GameManager::getInstance().onStart();
	EnemyManager::getInstance().onStart();
	BuffManager::getInstance().onStart();
	BulletManager::getInstance().onStart();
}

void BaseGameLoop::update(CDC * dc, CDC * canvasDC)
{

	if(!GameManager::getInstance().gameStart)
	{
		menu->draw(dc, canvasDC, 0, 0, 620, 625, 0, 0, SRCCOPY);
		DRAW_IMG(dc, canvasDC, music, 20, 460);
		DRAW_IMG(dc, canvasDC, startGame, 20, 400);

		if (Input::getInstance().lButtonDown)
		{
			if (Input::getInstance().mouseX > 20 && Input::getInstance().mouseX < 150 &&
				Input::getInstance().mouseY > 460 && Input::getInstance().mouseY < 537)
			{
				if (!playMusic)
					_playMusic();
				else
					MusicManager::stopMusic();

				playMusic = !playMusic;

			}
		}

		if(Input::getInstance().lButtonDown)
		{
			if(Input::getInstance().mouseX > 20 && Input::getInstance().mouseX < 170 &&
				Input::getInstance().mouseY > 400 && Input::getInstance().mouseY < 471)
			{				
				GameManager::getInstance().gameStart = true;
				MusicManager::stopMusic();
			}
		}

		return;
	}

	InputSignal::getInstance().tick();
	GameManager::getInstance().update(dc, canvasDC);
	EnemyManager::getInstance().update(dc, canvasDC);
	BuffManager::getInstance().update(dc, canvasDC);
	BulletManager::getInstance().update(dc, canvasDC);

}

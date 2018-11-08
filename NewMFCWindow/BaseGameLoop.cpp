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
	musicString[0].assign("01. ��ҹ������ Eastern Night");
	musicString[1].assign("02. ��ҕ��ҹ���� Ghostly Eyes");
	musicString[2].assign("03. �������¡��� Mooned Insect");
	musicString[3].assign("04. ҹȸ�θ������� Night Bird");
	musicString[4].assign("05. �⤦�褷�������ʤ�");
	musicString[5].assign("06. ���������|����Ѫ���� Old World");
	musicString[6].assign("07. �ץ쥤�󥨥�����");
	musicString[7].assign("08. ��ҹ�Έ󤤡��� Imperishable Night");
	musicString[8].assign("09. ��Ů�_�������� Dream Battle");
	musicString[9].assign("10. ��ɫ�ޥ����`���ѩ`��");
	musicString[10].assign("11. ����ǥ�饱�`������ Kagome-Kagome");
	musicString[11].assign("12. ��ݤ�ͫ���� Invisible Full Moon");
	musicString[12].assign("13. ������`����1969");
	musicString[13].assign("14. ǧ������_���� History of the Moon");
	musicString[14].assign("15. ��ȡ�w�衡�� Lunatic Princess");
	musicString[15].assign("16. ������`����1970");
	musicString[16].assign("17. �������ƥ�ɥ��å��塡�� ������");
	musicString[17].assign("18. �¤ޤǽ줱�������Ο�");
	musicString[18].assign("19. ��Ҋ��");
	musicString[19].assign("20. Eternal Dream���� �������ʘ�");
	musicString[20].assign("21. �|������С�");
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

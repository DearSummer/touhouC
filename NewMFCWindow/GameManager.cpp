#include "GameManager.h"
#include <vector>
#include "EnemyPlane.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "Circle.h"
#include "Time.h"
#include "BuffManager.h"
#include "Util.h"
#include "MusicManager.h"


void GameManager::setNum(CDC * dc, CDC* canvasDC, int num, int x, int y) const
{

	if (num < 0)
		num = 0;
	else if (num > 9)
		num = 9;

	this->num->draw(dc, canvasDC, x, y, 11, 15, 110 + num * 11, 0, SRCAND);
	this->num->draw(dc, canvasDC, x, y, 11, 15, 11 * num, 0, SRCPAINT);
}

void GameManager::enemyGetDamage(int index,int bulletIndex,int damage)
{
	enemyPlaneList[index]->getHurt(damage);
	BulletManager::getInstance().removePlayerBullet(bulletIndex);
}

void GameManager::drawLifeStar(CDC * dc, CDC * canvasDC) const
{
	const int hp = player->getHp();
	for (int i = 0; i < hp; i++)
	{
		DRAW_IMG(dc, canvasDC, lifeStar, 480 + 16 * i, 60);
	}
}

void GameManager::drawSkillStar(CDC * dc, CDC * canvasDC) const
{
	const int skill = player->getSkillCount();
	for(int i =0;i < skill;i++)
	{
		DRAW_IMG(dc, canvasDC, skillStar, 480 + 16 * i, 98);
	}
}

void GameManager::initMusic()
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

void GameManager::playMusic() const
{
	char buffer[256] = { 0 };
	sprintf_s(buffer, "res/music/%s.mid", musicString[musicIndex].c_str());

	MusicManager::getInstance().playBackGroundMusic(buffer);
}

GameManager::GameManager():musicIndex(0),gameStart(false)
{
	bgAttr = new Sprite("res/bg_attr.bmp", 210, 600);
	life = new Sprite("res/life.bmp", 80, 38);
	lifeStar = new Sprite("res/life_star.bmp", 32, 16);
	skill = new Sprite("res/skill.bmp", 80, 35);
	skillStar = new Sprite("res/skill_star.bmp", 32, 16);
	atk = new Sprite("res/atk.bmp", 40, 27);
	num = new Sprite("res/num.bmp", 220, 15);
	level = new Sprite("res/level.bmp", 80, 30);

	player = new Character;
	background = new Animation("res/bg/yuki", 392, 566, 31);

	
}


GameManager::~GameManager()
{
	delete player;
	delete background;
	delete bgAttr;
	delete life;
	delete lifeStar;
	delete skill;
	delete skillStar;
	delete atk;
	delete level;
	delete num;
}

GameManager & GameManager::getInstance()
{
	// TODO: insert return statement here
	static GameManager instance;
	return instance;
}

void GameManager::onStart()
{
	initMusic();
	//playMusic();

	player->onStart();
}

void GameManager::update(CDC * dc, CDC * canvasDC)
{

	if(MusicManager::getMusicState() == MUSIC_STATE_STOPPED)
	{
		musicIndex++;
		musicIndex %= 21;
		playMusic();
	}

	if(player->die)
	{
		//gameStart = false;
		finishGame();
		MusicManager::stopMusic();
		return;
	}

	background->draw(dc, canvasDC, 0, 0, Time.detlaTime * 1);
	bgAttr->draw(dc, canvasDC, 390, 0, 210, 600, 0, 0, SRCCOPY);
	life->draw(dc, canvasDC, 400, 50, 80, 38, 0, 0, SRCCOPY);
	skill->draw(dc, canvasDC, 400, 90, 80, 35, 0, 0, SRCCOPY);
	atk->draw(dc, canvasDC, 430, 450, 80, 54, 0, 0, SRCCOPY);
	level->draw(dc, canvasDC, 430, 400, 80, 30, 0, 0, SRCCOPY);

	setNum(dc, canvasDC, player->getLevel(), 510, 407);
	setNum(dc, canvasDC, player->getAtk(), 485, 455);

	drawLifeStar(dc, canvasDC);
	drawSkillStar(dc, canvasDC);

	player->update(dc, canvasDC);

	enemyPlaneList = EnemyManager::getInstance().getEnemyList();
	enemyBulletList = BulletManager::getInstance().getEnemyBullet();

	playerBulletList = BulletManager::getInstance().getPlayerBullet();

	buffList = BuffManager::getInstance().getBuffList();

	checkPlayerBulletToEnemy();
	checkEnemyBulletToPlayer();

	checkPlayerBuff();

	
}

void GameManager::checkPlayerBulletToEnemy()
{
	for (int i = 0; static_cast<int>(i) < playerBulletList.size(); i++)
	{
		if (!playerBulletList[i])
			continue;

		const Rect collider = playerBulletList[i]->getCollider();
		const int damage = playerBulletList[i]->getDamage();
		const BulletType bt = playerBulletList[i]->getBulletType();
		for (int j = 0; static_cast<int>(j) < enemyPlaneList.size(); j++)
		{

			if (!enemyPlaneList[j])
				continue;

			if (bt == BULLET_TYPE_CIRCLE)
			{
				if (circleToSquareCollider(Circle(collider.x + collider.width / 2, collider.y + collider.height / 2, static_cast<float>(collider.width) / 2),
					enemyPlaneList[j]->getCollider()))
				{
					enemyGetDamage(j, i, damage);
				}
			}

			if (bt == BULLET_TYPE_RECT)
			{
				if (squareToSquareCollider(collider, enemyPlaneList[j]->getCollider()))
				{
					enemyGetDamage(j, i, damage);
				}
			}

		}
	}
}

void GameManager::checkEnemyBulletToPlayer()
{
	if(player->invincible)
		return;

	for(int i = 0;static_cast<int>(i) < enemyBulletList.size();i++)
	{
		if(!enemyBulletList[i])
			continue;

		const Rect collider = enemyBulletList[i]->getCollider();
		const BulletType bt = enemyBulletList[i]->getBulletType();

		if(bt == BULLET_TYPE_CIRCLE)
		{
			if( circleToSquareCollider(Circle(collider.x + collider.width / 2,collider.y + collider.height / 2,static_cast<float>(collider.width) / 2),
				player->getCollider()))
			{
				player->getHurt();
				BulletManager::getInstance().removeEnemyBullet(i);
			}
		}

		if(bt == BULLET_TYPE_RECT)
		{
			if(squareToSquareCollider(collider,player->getCollider()))
			{
				player->getHurt();
				BulletManager::getInstance().removeEnemyBullet(i);
			}
		}
	}
}

void GameManager::checkPlayerBuff()
{
	if (player->invincible)
		return;

	for(int i =0;static_cast<int>(i) < buffList.size();i++)
	{
		if (!buffList[i])
			continue;

		Buff * buff = buffList[i];

		if(buff->getBuffType() == BUFF_TYPE_COLLIDER_ON)
		{
			if(squareToSquareCollider(buff->getCollider(),player->getCollider()))
			{
				player->setBuff(buff->getPlayerBuffType());
				BuffManager::getInstance().removeBuff(i);
			}
			
		}


	}
}

bool GameManager::circleToSquareCollider(Circle circle, Rect rect) const
{
	Point closePoint(rect.x, rect.y);
	if(circle.x < rect.x)
	{
		closePoint.x = rect.x;
	}
	else if(circle.x > rect.x + rect.width)
	{
		closePoint.x = rect.x + rect.width;
	}
	else
	{
		closePoint.x = circle.x;
	}

	if(circle.y < rect.y)
	{
		closePoint.y = rect.y;
	}
	else if(circle.y > rect.y + rect.height)
	{
		closePoint.y = rect.y;
	}
	else
	{
		closePoint.y = circle.y;
	}

	const float distance = sqrt(pow(closePoint.x - circle.x, 2) + pow(closePoint.y - circle.y, 2));

	return distance <= circle.r;
}

bool GameManager::squareToSquareCollider(const Rect a, const Rect b)
{
	return a.x < b.x + b.width &&
		   a.x + a.width > b.x && 
		   a.y < b.y + b.height && 
		   a.height + a.y > b.y;
}


void GameManager::finishGame()
{
	gameStart = false;
	player->reset();
	EnemyManager::getInstance().reset();
	BulletManager::getInstance().reset();
	BuffManager::getInstance().reset();
}

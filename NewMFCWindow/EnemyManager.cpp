#include "EnemyManager.h"
#include "Time.h"
#include "BuffManager.h"
#include "MusicManager.h"
#include "Crash.h"
#include "Math.h"
#include "GameManager.h"


EnemyManager::EnemyManager():timer(0)
{
	iku = new Iku();
	remilia = new Remilia();

	atkBuff = new PowerBuff("res/buff/power_buff.bmp", 32, 16);
	atkBuff->setPlayerBuffType(ADD_DAMAGE);

	expBuff = new PowerBuff("res/buff/exp_buff.bmp", 32, 16);
	expBuff->setPlayerBuffType(ADD_EXP);

	bossHp = new Sprite("res/boss_hp.bmp", 390, 3);
}



EnemyManager & EnemyManager::operator=(const EnemyManager & e) const
{
	// TODO: insert return statement here
	return getInstance();
}

void EnemyManager::addCrash(Point p)
{
	Crash * c = new Crash("res/crash/crash", 64, 64, 10, Point(0, 0));
	c->setPos(p);

	BuffManager::getInstance().addBuff(c);
	MusicManager::playDieSound();
}

void EnemyManager::addBuff(PowerBuff * b,Point pos)
{
	PowerBuff * pb = dynamic_cast<PowerBuff*>(b->clone());
	pb->setPos(pos);
	BuffManager::getInstance().addBuff(pb);
}

void EnemyManager::drawEnemy(CDC * dc, CDC * canvasDC)
{
	for (int i = 0;static_cast<int>(i) < enemyList.size(); i++)
	{
		if (!enemyList[i])
			continue;

		if(enemyList[i]->isBoss)
		{
			drawBossHeath(dc, canvasDC, 
				Math::lerp(bossHp->getRect().width, static_cast<float>(enemyList[i]->getHp()) / enemyList[i]->getMaxHp() * 390, 0.1f));
		}

		if (enemyList[i]->getState() == DISPLAY)
		{
			enemyList[i]->update(dc, canvasDC);
		}
		else if (enemyList[i]->getState() == DIE_OUT_OF_RANGE)
		{
			removeEnemy(i);
		}
		else if(enemyList[i]->getState() == DIE_BY_SHOOT)
		{
			if (enemyList[i]->isBoss)
			{
				GameManager::getInstance().finishGame();
				break;
			}
				
			addCrash(enemyList[i]->getPos());
			srand(GetTickCount());
			const int r = rand() % 30;
			if(r <= 10)
			{
				if (r <= 2)
				{
					addBuff(atkBuff, enemyList[i]->getPos());
				}
				else if (r <= 6)
				{
					addBuff(expBuff, enemyList[i]->getPos());
				}
				
			}
			removeEnemy(i);
		}

	}
}

void EnemyManager::addEnemy(EnemyPlane * enemy)
{
	for(int i = 0;static_cast<int>(i) < enemyList.size();i++)
	{
		if (!enemyList[i])
		{
			enemyList[i] = enemy;
			return;
		}
			
	}

	enemyList.push_back(enemy);
}

void EnemyManager::drawBossHeath(CDC * dc, CDC * canvasDC, float length) const
{
	bossHp->draw(dc, canvasDC, 0, 0, length, 3, 0, 0, SRCCOPY);
}

void EnemyManager::createLevel1()
{
	if (timer < 400 || level1Count < 0)
		return;
	timer = 0;

	Iku * newIku = dynamic_cast<Iku *>(iku->clone());
	if (level1Count <= 10)
		newIku->b_circle = false;
	srand(GetTickCount());

	if(newIku->getStage() == E_STAGE_2)
	{
		newIku->setBirthPos(Point(20 + rand() % 160, 0));
	}

	if(rand() % 2 == 1)
	{
		newIku->b_mirror = true;
	}else
	{
		newIku->b_mirror = false;
	}
	addEnemy(newIku);
	level1Count--;

	if(level1Count == 0 && iku->getStage() == E_STAGE_1)
	{
		iku->setStage(E_STAGE_2);
		level1Count = 30;
		iku->setBirthPos(Point(110, 0));
	}
	else if (level1Count == 0 && iku->getStage() == E_STAGE_2)
	{
		createLevel1Boss();
	}
}

void EnemyManager::createLevel1Boss()
{
	addEnemy(remilia);
}


EnemyManager& EnemyManager::getInstance()
{
	static EnemyManager instance;
	return instance;
}

EnemyManager::~EnemyManager()
{
	delete iku;
}

std::vector<EnemyPlane*>& EnemyManager::getEnemyList()
{
	// TODO: insert return statement here
	return enemyList;
}

void EnemyManager::removeEnemy(int index)
{

	if (index < 0 || index >= enemyList.size())
		return;

	delete enemyList[index];
	enemyList[index] = nullptr;
}

void EnemyManager::destoryAllEnemy()
{
	for(int i = 0;static_cast<int>(i) < enemyList.size();i++)
	{
		if (!enemyList[i])
			continue;

		if(enemyList[i]->isBoss)
			continue;

		enemyList[i]->setState(DIE_BY_SHOOT);
	}
}

void EnemyManager::onStart()
{
	remilia->onStart();
	iku->onStart();
}

void EnemyManager::update(CDC * dc, CDC * canvasDC)
{
	timer += Time.detlaTime;
	createLevel1();
	drawEnemy(dc, canvasDC);
}


void EnemyManager::reset()
{
	level1Count = 20;
	iku->setStage(E_STAGE_1);
	timer = 0;

	enemyList.clear();
}

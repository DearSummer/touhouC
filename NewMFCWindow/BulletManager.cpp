#include "BulletManager.h"

BulletManager::BulletManager()
{
	playerBulletList.clear();
	enemyBulletList.clear();
}


BulletManager::~BulletManager()
{
}



BulletManager& BulletManager::getInstance()
{
	static BulletManager instance;
	return instance;
}

void BulletManager::addPlayerBullet( Bullet * bullet)
{
	for(int i = 0; static_cast<int>(i) < playerBulletList.size();i++)
	{
		if (!playerBulletList[i])
		{
			playerBulletList[i] = bullet;
			return;
		}			
	}
	playerBulletList.push_back(bullet);
}

void BulletManager::addEnemyBullet(Bullet * bullet)
{
	for(int i= 0;static_cast<int>(i) < enemyBulletList.size();i++)
	{
		if(!enemyBulletList[i])
		{
			enemyBulletList[i] = bullet;
			return;
		}
	}

	enemyBulletList.push_back(bullet);
}

void BulletManager::destoryAllBullet()
{
	for(int i = 0;i < enemyBulletList.size();i++)
	{
		if(!enemyBulletList[i])
			continue;

		enemyBulletList[i]->setState(DIE_OUT_OF_RANGE);
	}
}

void BulletManager::removeEnemyBullet(int index)
{
	delete enemyBulletList[index];
	enemyBulletList[index] = nullptr;
}

void BulletManager::removePlayerBullet(int index)
{
	delete playerBulletList[index];
	playerBulletList[index] = nullptr;
}

std::vector<Bullet*>& BulletManager::getPlayerBullet()
{
	// TODO: insert return statement here
	return playerBulletList;
}

std::vector<Bullet*>& BulletManager::getEnemyBullet()
{
	// TODO: insert return statement here
	return enemyBulletList;
}



void BulletManager::onStart()
{
}

void BulletManager::update(CDC * dc, CDC * canvasDC)
{
	drawPlayerBullet(dc, canvasDC);
	drawEnemyBullet(dc, canvasDC);
}

void BulletManager::reset()
{
	playerBulletList.clear();
	enemyBulletList.clear();
}

void BulletManager::drawPlayerBullet(CDC * dc, CDC * canvasDC)
{
	for (int i = 0; static_cast<int>(i) < playerBulletList.size(); i++)
	{
		if (!playerBulletList[i])
			continue;

		if (playerBulletList[i]->getState() == DISPLAY)
		{
			playerBulletList[i]->draw(dc, canvasDC);
		}
		else if (playerBulletList[i]->getState() == DIE_OUT_OF_RANGE)
		{
			delete playerBulletList[i];
			playerBulletList[i] = nullptr;
		}
	}
}

void BulletManager::drawEnemyBullet(CDC * dc, CDC * canvasDC)
{
	for(int i = 0; static_cast<int>(i)< enemyBulletList.size();i++)
	{
		if(!enemyBulletList[i])
			continue;

		if(enemyBulletList[i]->getState() == DISPLAY)
		{
			enemyBulletList[i]->draw(dc, canvasDC);
		}
		else if(enemyBulletList[i]->getState() == DIE_OUT_OF_RANGE)
		{
			delete enemyBulletList[i];
			enemyBulletList[i] = nullptr;
		}
	}

}


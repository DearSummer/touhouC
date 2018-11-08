#pragma once
#include "IGameLoop.h"
#include <vector>
#include "Bullet.h"

class BulletManager :
	public IGameLoop
{

	std::vector<Bullet *> playerBulletList;
	std::vector<Bullet *> enemyBulletList;

	BulletManager();
	~BulletManager();

	void drawPlayerBullet(CDC * dc, CDC * canvasDC);
	void drawEnemyBullet(CDC * dc, CDC * canvasDC);

public:
	
	static BulletManager& getInstance();

	void addPlayerBullet(Bullet * bullet);
	void addEnemyBullet(Bullet * bullet);

	void destoryAllBullet();

	void removeEnemyBullet(int index);
	void removePlayerBullet(int index);

	std::vector<Bullet *> & getPlayerBullet();
	std::vector<Bullet *> & getEnemyBullet();
	
	void onStart() override;
	void update(CDC* dc, CDC* canvasDC) override;
	void reset();
	
};


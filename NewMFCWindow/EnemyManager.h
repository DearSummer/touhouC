#pragma once
#include "IGameLoop.h"
#include <vector>
#include "Iku.h"
#include "PowerBuff.h"
#include "Remilia.h"

class EnemyManager : IGameLoop
{
	std::vector<EnemyPlane *> enemyList;

	Sprite * bossHp;

	Iku * iku;
	Remilia * remilia;

	PowerBuff * atkBuff;
	PowerBuff * expBuff;

	//Crash * crash;

	float timer;

	EnemyManager();
	EnemyManager(const EnemyManager&) = default;
	EnemyManager& operator=(const EnemyManager& e) const;

	static void addCrash(Point p);
	static void addBuff(PowerBuff * b,Point pos);

	void drawEnemy(CDC * dc,CDC * canvasDC);
	void addEnemy(EnemyPlane * enemy);

	void drawBossHeath(CDC *dc, CDC * canvasDC,float length) const;

	int level1Count = 20;

	void createLevel1();
	void createLevel1Boss();

public:

	static EnemyManager& getInstance();

	~EnemyManager();

	std::vector<EnemyPlane *> & getEnemyList();
	void removeEnemy(int index);
	void destoryAllEnemy();

	void onStart() override;
	void update(CDC* dc, CDC* canvasDC) override;

	void reset();
};


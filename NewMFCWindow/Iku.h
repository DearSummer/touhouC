#pragma once
#include "EnemyPlane.h"
#include "NormalBullet.h"
#include "IkuBullet.h"
#include "RandomLineBullet.h"

class Iku
	:public EnemyPlane
{
	float timer, angle, lineX;

	IkuBullet * normalBullet;
	RandomLineBullet * randomLineBullet;

	void circleRoad();
	void lineRoad();

	bool b_stage2_mirror,frist_into_stage2;
	float stage2_r;

	void initStage2();

	void stage1();
	void stage2();

public:
	Iku();
	~Iku();

	bool b_mirror;
	bool b_circle;

	void onStart() override;
	void update(CDC* dc, CDC* canvasDC) override;
	void move() override;
	void shoot() override;

	EnemyPlane* clone() override;
	void getHurt(int damage) override;
};


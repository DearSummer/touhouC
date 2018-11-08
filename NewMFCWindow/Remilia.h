#pragma once
#include "EnemyPlane.h"
#include "AngleBullet.h"
#include "RandomLineBullet.h"
#include "SlowedBullet.h"

class Remilia
	:public EnemyPlane
{
	std::vector<Point> road;

	AngleBullet * defauleBullet;
	RandomLineBullet * randomLineBullet;
	SlowedBullet * slowedBullet;
	AngleBullet * screwBullet;

	int roadIndex;

	bool b_screw;
	int angle;

	void shootScrewBullet();
	void shootCircleBullet() const;
	void shootNormalBullet() const;
	void shootSlowedBullet() const;

	Point getCurrentPoint() const;

public:
	Remilia();
	~Remilia();

	void onStart() override;
	void update(CDC* dc, CDC* canvasDC) override;
	void move() override;
	void shoot() override;
	EnemyPlane* clone() override;
	void getHurt(int damage) override;

	int getCurrentHp() const;
};


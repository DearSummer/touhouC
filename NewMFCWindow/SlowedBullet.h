#pragma once
#include "Bullet.h"
class SlowedBullet :
	public Bullet
{
	float angle;
public:
	SlowedBullet();
	~SlowedBullet();
	SlowedBullet(const std::string & path, int width, int height, float aliveTime);

	void draw(CDC* dc, CDC* canvasDC) override;
	Bullet* clone() override;
	BulletType getBulletType() override;

	void setAngle(float angle);
};


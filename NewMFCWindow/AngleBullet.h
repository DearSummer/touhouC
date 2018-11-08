#pragma once
#include "Bullet.h"
class AngleBullet :
	public Bullet
{
	float angle;
public:
	AngleBullet(const std::string& path, int width, int height, float aliveTime);
	AngleBullet();
	~AngleBullet();

	void setAngle(float angle);

	void draw(CDC* dc, CDC* canvasDC) override;
	Bullet* clone() override;
	BulletType getBulletType() override;
};


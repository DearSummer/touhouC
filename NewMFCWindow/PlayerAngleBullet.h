#pragma once
#include "Bullet.h"

class PlayerAngleBullet
	:public Bullet
{
	float angle;
public:
	PlayerAngleBullet(const std::string& path, int width, int height);
	PlayerAngleBullet();
	~PlayerAngleBullet();

	void draw(CDC* dc, CDC* canvasDC) override;
	Bullet* clone() override;
	BulletType getBulletType() override;

	void setAngle(float angle);
};


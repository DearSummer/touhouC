#pragma once
#include "Bullet.h"

class RandomLineBullet:public Bullet
{

private:
	float angle;

	static float randomAngle();
public:
	RandomLineBullet(const std::string& path, int width, int height, float aliveTime);
	RandomLineBullet();
	~RandomLineBullet();


	void draw(CDC* dc, CDC* canvasDC) override;
	Bullet* clone() override;
	BulletType getBulletType() override;
};


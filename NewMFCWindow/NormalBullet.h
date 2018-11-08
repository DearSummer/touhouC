#pragma once
#include "Bullet.h"
class NormalBullet :
	public Bullet
{

public:
	NormalBullet(const std::string& path, int width, int height, float aliveTime);
	NormalBullet();
	~NormalBullet();

	void draw(CDC* dc, CDC* canvasDC) override;
	Bullet* clone() override;
	BulletType getBulletType() override;
};


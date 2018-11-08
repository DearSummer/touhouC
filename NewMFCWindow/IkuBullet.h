#pragma once
#include "Bullet.h"

class IkuBullet
	:public Bullet
{
	void setOffset();
	int offset = 0;
public:
	IkuBullet(const std::string& path, int width, int height, float aliveTime);
	IkuBullet();
	~IkuBullet();


	void draw(CDC* dc, CDC* canvasDC) override;
	Bullet* clone() override;
	BulletType getBulletType() override;
};


#include "AngleBullet.h"
#include "Util.h"
#include "Time.h"
#include "Math.h"


AngleBullet::AngleBullet(const std::string & path, int width, int height, float aliveTime)
	:Bullet(path,width,height,aliveTime),angle(0)
{
}

AngleBullet::AngleBullet():angle(0)
{
}


AngleBullet::~AngleBullet()
= default;

void AngleBullet::setAngle(float angle)
{
	this->angle = angle;
}

void AngleBullet::draw(CDC * dc, CDC * canvasDC)
{
	bulletPos.y -= cos(angle / PI) * speed;
	bulletPos.x += sin(angle / PI) * speed;

	if (bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.x > 390 || bulletPos.y > 560)
		state = DIE_OUT_OF_RANGE;
	else
		state = DISPLAY;
	

	if (isDead())
		return;

	timer += Time.detlaTime;
	DRAW_IMG(dc, canvasDC, bullet, bulletPos.x, bulletPos.y);
}

Bullet * AngleBullet::clone()
{
	AngleBullet * b = new AngleBullet();
	b->bullet = bullet;
	b->bulletPos = bulletPos;
	b->aliveTime = aliveTime;
	b->speed = speed;
	b->state = state;
	b->damage = damage;
	b->angle = angle;
	return b;
}


BulletType AngleBullet::getBulletType()
{
	return BULLET_TYPE_CIRCLE;
}

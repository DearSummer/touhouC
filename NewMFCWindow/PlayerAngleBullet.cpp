#include "PlayerAngleBullet.h"
#include "Util.h"
#include "Time.h"
#include "Math.h"



PlayerAngleBullet::PlayerAngleBullet(const std::string & path, int width, int height)
	:Bullet(path,width,height,BULLET_NEVER_DIE_WITH_TIME),angle(0)
{
}

PlayerAngleBullet::PlayerAngleBullet():angle(0)
{
}


PlayerAngleBullet::~PlayerAngleBullet()
= default;

void PlayerAngleBullet::draw(CDC * dc, CDC * canvasDC)
{
	if (bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.x > 390 || bulletPos.y > 560)
		state = DIE_OUT_OF_RANGE;
	else
		state = DISPLAY;

	bulletPos.y -= cos(PI / 180 * angle) * speed;
	bulletPos.x += sin(PI / 180 * angle) * speed;

	if (isDead())
		return;

	timer += Time.detlaTime;
	DRAW_IMG(dc, canvasDC, bullet, bulletPos.x, bulletPos.y);
}

Bullet * PlayerAngleBullet::clone()
{
	PlayerAngleBullet * b = new PlayerAngleBullet();
	b->bullet = bullet;
	b->bulletPos = bulletPos;
	b->aliveTime = aliveTime;
	b->speed = speed;
	b->state = state;
	b->damage = damage;
	b->angle = angle;
	return b;
}



BulletType PlayerAngleBullet::getBulletType()
{
	return BULLET_TYPE_CIRCLE;
}

void PlayerAngleBullet::setAngle(float angle)
{
	this->angle = angle;
}

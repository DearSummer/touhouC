#include "RandomLineBullet.h"
#include "Util.h"
#include "Time.h"
#include "Math.h"


float RandomLineBullet::randomAngle()
{
	srand(GetTickCount());
	return rand() % 40 - 20;
}

RandomLineBullet::RandomLineBullet(const std::string & path, int width, int height, float aliveTime)
	:Bullet(path, width, height, aliveTime)
{
	angle = randomAngle();
}

RandomLineBullet::RandomLineBullet()
= default;


RandomLineBullet::~RandomLineBullet()
= default;

void RandomLineBullet::draw(CDC * dc, CDC * canvasDC)
{

	if (bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.x > 390 || bulletPos.y > 560)
		state = DIE_OUT_OF_RANGE;
	else
		state = DISPLAY;

	bulletPos.y += cos(angle / PI) * speed;
	bulletPos.x += sin(angle / PI) * speed;

	if (isDead())
		return;

	timer += Time.detlaTime;
	DRAW_IMG(dc, canvasDC, bullet, bulletPos.x, bulletPos.y);
}

Bullet * RandomLineBullet::clone()
{
	RandomLineBullet * b = new RandomLineBullet();
	b->bullet = bullet;
	b->bulletPos = bulletPos;
	b->aliveTime = aliveTime;
	b->speed = speed;
	b->state = DISPLAY;
	b->damage = damage;
	b->angle = randomAngle();
	return b;
}



BulletType RandomLineBullet::getBulletType()
{
	return BULLET_TYPE_CIRCLE;
}

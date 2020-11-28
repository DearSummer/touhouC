#include "IkuBullet.h"
#include "Util.h"
#include "Time.h"


void IkuBullet::setOffset()
{
	srand(GetTickCount());
	offset = rand() % 5 - 3;
}

IkuBullet::IkuBullet(const std::string & path, int width, int height, float aliveTime)
	:Bullet(path,width,height,aliveTime)
{
	setOffset();
}

IkuBullet::IkuBullet()
{
	setOffset();
}


IkuBullet::~IkuBullet()
{
}

void IkuBullet::draw(CDC * dc, CDC * canvasDC)
{
	if (bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.x > 390 || bulletPos.y > 560)
		state = State::DIE_OUT_OF_RANGE;
	else
		state = State::DISPLAY;

	bulletPos.y += speed;
	bulletPos.x += offset;
	if (isDead())
		return;

	timer += Time.detlaTime;
	DRAW_IMG(dc, canvasDC, bullet, bulletPos.x, bulletPos.y);
}

Bullet * IkuBullet::clone()
{
	IkuBullet * b = new IkuBullet();
	b->bullet = bullet;
	b->bulletPos = bulletPos;
	b->aliveTime = aliveTime;
	b->speed = speed;
	b->state = state;
	return b;
}



BulletType IkuBullet::getBulletType()
{
	return BulletType::BULLET_TYPE_CIRCLE;
}

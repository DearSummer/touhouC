#include "NormalBullet.h"
#include "Util.h"
#include "Time.h"
#include "BulletManager.h"




NormalBullet::NormalBullet(const std::string& path, int width, int height, float aliveTime)
	:Bullet(path, width, height, aliveTime)
{
}

NormalBullet::NormalBullet()
= default;


NormalBullet::~NormalBullet()
= default;

void NormalBullet::draw(CDC * dc, CDC * canvasDC)
{
	if (bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.x > 390 || bulletPos.y > 560)
		state = State::DIE_OUT_OF_RANGE;
	else
		state = State::DISPLAY;

	bulletPos.y -= speed;
	

	if (isDead())
		return;

	timer += Time.detlaTime;
	DRAW_IMG(dc, canvasDC, bullet, bulletPos.x, bulletPos.y);

}



Bullet * NormalBullet::clone()
{
	NormalBullet * b = new NormalBullet();
	b->bullet = bullet;
	b->bulletPos = bulletPos;
	b->aliveTime = aliveTime;
	b->speed = speed;
	b->state = state;
	b->damage = damage;
	return b;
}

BulletType NormalBullet::getBulletType()
{
	return BulletType::BULLET_TYPE_CIRCLE;
}

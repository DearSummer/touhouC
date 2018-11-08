#include "Remilia.h"
#include "BulletManager.h"
#include "Math.h"


void Remilia::shootScrewBullet()
{
	shooter->reload(screwBullet);
	shooter->setReloadTime(30);
	AngleBullet * b = dynamic_cast<AngleBullet*>(shooter->fire());
	if (!b)
		return;

	b->setAngle(angle);
	b->setPos(getCurrentPoint());
	BulletManager::getInstance().addEnemyBullet(b);

	if(angle == 360)
	{
		angle = 0;
		b_screw = false;

		shooter->setReloadTime(300);
	}

	angle += 5;
}

void Remilia::shootCircleBullet() const
{
	for(int i = 0;i < 36;i++)
	{
		shooter->reload(defauleBullet);
		AngleBullet * b = dynamic_cast<AngleBullet*>(shooter->fire());
		if (!b)
			continue;

		srand(GetTickCount());
		const int r = rand() % 2;
		if (r == 1)
			b->setAngle(-i * 10);
		else
			b->setAngle(i * 10);
		b->setPos(getCurrentPoint());
		BulletManager::getInstance().addEnemyBullet(b);
	}
}

void Remilia::shootNormalBullet() const
{
	shooter->reload(randomLineBullet);
	Bullet * bullet = shooter->fire();
	if (!bullet)
		return;
	srand(GetTickCount());
	bullet->setPos(Point(actorPos.x + rand() % 12 - 6, actorPos.y + rand() % 12 - 6));
	BulletManager::getInstance().addEnemyBullet(bullet);
}

void Remilia::shootSlowedBullet() const
{
	for(int i = 0;i < 36;i++)
	{
		shooter->reload(slowedBullet);
		SlowedBullet * b = dynamic_cast<SlowedBullet*>(slowedBullet->clone());
		if (!b)
			continue;

		srand(GetTickCount());
		const int r = rand() % 2;
		if (r == 1)
			b->setAngle(-i * 10);
		else
			b->setAngle(i * 10);
		b->setPos(getCurrentPoint());
		BulletManager::getInstance().addEnemyBullet(b);
	}
}

Point Remilia::getCurrentPoint() const
{
	Point p;
	p.x = actorPos.x + 32;
	p.y = actorPos.y + 32;
	return p;
}

Remilia::Remilia():roadIndex(0),b_screw(false),angle(0)
{
	player = new Animation("res/enemy/remilia", 128, 64, 8);

	defauleBullet = new AngleBullet("res/bullet/bullet_1.bmp", 32, 16, BULLET_NEVER_DIE_WITH_TIME);
	randomLineBullet = new RandomLineBullet("res/bullet/bullet_2.bmp", 32, 16, BULLET_NEVER_DIE_WITH_TIME);
	slowedBullet = new SlowedBullet("res/bullet/bullet_3.bmp", 32, 16, 10000);
	screwBullet = new AngleBullet("res/bullet/bullet_4.bmp", 32, 16, BULLET_NEVER_DIE_WITH_TIME);

	screwBullet->setSpeed(5.2f);
	defauleBullet->setSpeed(5.0f);
	randomLineBullet->setSpeed(4.0f);
	slowedBullet->setSpeed(3.5f);

	shooter = new Shooter(defauleBullet, 300);

	setCollider(64, 64);

	isBoss = true;
}


Remilia::~Remilia()
= default;

void Remilia::onStart()
{
	setAttributes(1000, 5.0f, 1, 4);
	maxHp = getHp();

	road.emplace_back(22, 96);
	road.emplace_back(195, 40);
	road.emplace_back(310, 138);
	road.emplace_back(320, 123);
	road.emplace_back(23, 123);
	road.emplace_back(43, 153);
	road.emplace_back(129, 32);
	road.emplace_back(287, 100);
	road.emplace_back(298, 25);
	road.emplace_back(65, 87);
}

void Remilia::update(CDC * dc, CDC * canvasDC)
{
	shooter->tick();

	move();
	shoot();

	player->drawImg(dc, canvasDC, actorPos.x, actorPos.y, 80);
}

void Remilia::move()
{
	actorPos.x = ceil(Math::lerp(actorPos.x, road[roadIndex].x, 0.05f));
	actorPos.y = ceil(Math::lerp(actorPos.y, road[roadIndex].y, 0.05f));


	if(abs(actorPos.x - road[roadIndex].x) < 20 && abs(actorPos.y - road[roadIndex].y) < 20)
	{
		srand(GetTickCount());
		roadIndex = rand() % road.size();
	}

}

void Remilia::shoot()
{
	Bullet * bullet = shooter->fire();
	if (!bullet)
		return;

	if(b_screw)
	{
		shootScrewBullet();
		return;
	}
		
	srand(GetTickCount());
	const int r = rand() % 10;

	if (r <= 2)
		shootCircleBullet();
	else if (r <= 4)
		shootNormalBullet();
	else if (r <= 8)
		shootSlowedBullet();
	else
		b_screw = true;
}

EnemyPlane * Remilia::clone()
{
	return nullptr;
}

void Remilia::getHurt(int damage)
{
	hp -= damage;
}

int Remilia::getCurrentHp() const
{
	return hp;
}

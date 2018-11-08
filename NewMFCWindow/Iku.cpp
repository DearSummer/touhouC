#include "Iku.h"
#include "Time.h"
#include "Math.h"
#include "BulletManager.h"


void Iku::circleRoad()
{
	actorPos = circle(140, angle / PI);
	actorPos.y += angle * speed;

	if (b_mirror)
	{
		actorPos.x = 390 - actorPos.x;
	}

}

void Iku::lineRoad()
{
	actorPos.x = lineX;
	actorPos.y = 0.3 * lineX + 100;

	if (b_mirror)
		actorPos.x = 390 - actorPos.x;
}


void Iku::initStage2()
{
	stage2_r = actorPos.x;
	frist_into_stage2 = false;

	shooter->setReloadTime(600);
	normalBullet->setSpeed(4.5f);
	shooter->reload(randomLineBullet);
}

void Iku::stage1()
{
	if (b_circle)
		angle += 0.1;
	else
		lineX += speed;

	if (b_circle)
		circleRoad();
	else
		lineRoad();
}

void Iku::stage2()
{
	actorPos.y += speed;
	if(frist_into_stage2)
	{
		initStage2();
	}

	int y = actorPos.y;
	if (actorPos.y >= 250)
	{
		angle += 0.1;

		actorPos = circle(stage2_r, angle / PI);
		actorPos.y = y;

		if (b_stage2_mirror)
			actorPos.x = 390 - actorPos.x;
	}

	if (b_mirror)
	{
		actorPos.x = 390 - actorPos.x;
		b_stage2_mirror = true;
		b_mirror = false;
	}
		
}

Iku::Iku():timer(0),angle(0),b_mirror(false), b_circle(true),lineX(0),b_stage2_mirror(false),stage2_r(0),frist_into_stage2(true)
{
	player = new Animation("res/enemy/iku_enemy", 40, 40, 9);

	normalBullet = new IkuBullet("res/bullet/bullet_iku_0.bmp", 32, 16, BULLET_NEVER_DIE_WITH_TIME);
	normalBullet->setSpeed(4.0f);

	randomLineBullet = new RandomLineBullet("res/bullet/bullet_iku_0.bmp", 32, 16, BULLET_NEVER_DIE_WITH_TIME);
	randomLineBullet->setSpeed(4.5f);

	shooter = new Shooter(normalBullet, 500);

	setCollider(20, 40);

	speed = 3;
	srand(GetTickCount());
	speed += rand() % 3;

	setStage(E_STAGE_1);

	isBoss = false;
}


Iku::~Iku()
{
	delete normalBullet;
}

void Iku::onStart()
{
	maxHp = getHp();
}

void Iku::update(CDC * dc, CDC * canvasDC)
{
	shooter->tick();

	move();
	shoot();

	player->drawImg(dc, canvasDC, actorPos.x, actorPos.y, Time.detlaTime * 120);
}

void Iku::move()
{
	switch (stage)
	{
	case E_STAGE_1:
		stage1();
		break;
	case E_STAGE_2:
		stage2();
		break;
	default:
		break;
	}

}

void Iku::shoot()
{
	Bullet * bullet = shooter->fire();
	if (!bullet)
		return;

	bullet->setPos(Point(actorPos.x, actorPos.y));
	BulletManager::getInstance().addEnemyBullet(bullet);
}

EnemyPlane * Iku::clone()
{
	Iku * i = new Iku();
	i->hp = hp;
	i->speed = speed;
	i->stage = stage;
	i->actorPos = actorPos;
	return i;
}

void Iku::getHurt(int damage)
{
	hp -= damage;
}

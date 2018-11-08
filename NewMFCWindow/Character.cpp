#include "Character.h"
#include "Input.h"
#include "Time.h"
#include "Util.h"
#include "BulletManager.h"
#include "NormalBullet.h"
#include "InputSignal.h"
#include "BuffManager.h"
#include "EnemyManager.h"
#include "MusicManager.h"

void Character::getHurt()
{

	MusicManager::playDieSound();

	hp--;
	if (hp > 0)
		invincible = true;
	else
		die = true;
}


void Character::shootAngleBullet(int num) const
{
	int angle = 5;
	for(int i = 0;i < num;i++)
	{
		shooter->reload(angleBullet);
		PlayerAngleBullet * b = dynamic_cast<PlayerAngleBullet*>(shooter->fire());
		if(!b)
			continue;
		b->setAngle((i % 2 == 0 ? -1 : 1) * angle);
		b->setPos(actorPos);
		if (i % 2 == 1)
			angle += 5;

		BulletManager::getInstance().addPlayerBullet(b);
	}
}

void Character::shootNormalBullet() const
{
	shooter->reload(normalBullet);
	Bullet * newBullet = shooter->fire();
	if (!newBullet)
		return;
	newBullet->setPos(Point(actorPos.x, actorPos.y));

	BulletManager::getInstance().addPlayerBullet(newBullet);
}

void Character::useSkill()
{
	if (skill <= 0 || skillTimer < skillCD)
		return;

	skill--;
	skillTimer = 0;

	EnemyManager::getInstance().destoryAllEnemy();
	BulletManager::getInstance().destoryAllBullet();

	Buff * effect = skillEffect->clone();
	effect->setPos(Point(actorPos.x - 128,actorPos.y - 128));
	BuffManager::getInstance().addBuff(effect);
}

void Character::addLevelEffect(LevelUpEffect * effect)
{
	Buff * e = effect->clone();
	e->setPos(actorPos);
	speed += 0.3;
	shooter->setReloadTime(180 - 10 * level);
	BuffManager::getInstance().addBuff(e);

	MusicManager::playUpgradeSound();
}

void Character::drawHero(CDC* dc, CDC* canvasDC) const
{
	if (!left && !right)
		player_m->drawImg(dc, canvasDC, actorPos.x, actorPos.y, Time.detlaTime * 2);
	else if (left)
		DRAW_IMG(dc, canvasDC, player_l, actorPos.x, actorPos.y);
	else if (right)
		DRAW_IMG(dc, canvasDC, player_r, actorPos.x, actorPos.y);
}

void Character::invincibleStage(CDC* dc, CDC* canvasDC)
{
	invincibleTimer += Time.detlaTime;
	invincibleFrame++;

	if (invincibleFrame % 2 == 0)
		drawHero(dc, canvasDC);

	if (invincibleTimer > 2500)
	{
		invincibleTimer = 0;
		invincibleFrame = 0;
		invincible = false;
	}

}


Character::Character():right(false),left(false),skill(3),exp(0),skillTimer(1000),skillCD(1500),
	invincible(false),invincibleTimer(0),invincibleFrame(0),die(false)
{
	Actor::setAttributes(6, 5, 5, 1);

	player_m = new Animation("res/hero_m", 58, 47, 4);

	player_l = new Sprite("res/hero_l.bmp", 58, 47);
	player_r = new Sprite("res/hero_r.bmp", 58, 47);

	normalBullet = new NormalBullet("res/bullet/bullet_0.bmp", 32, 16, BULLET_NEVER_DIE_WITH_TIME);
	normalBullet->setDamage(damage);
	normalBullet->setSpeed(6);
	shooter = new Shooter(normalBullet, 180);

	angleBullet = new PlayerAngleBullet("res/bullet/bullet_6.bmp", 32, 16);
	angleBullet->setDamage(damage / 2);
	angleBullet->setSpeed(5.5f);

	levelUpTo2Effect = new LevelUpEffect("res/effect/level_up_2.bmp", 100, 11);
	levelUpTo3Effect = new LevelUpEffect("res/effect/level_up_3.bmp", 100, 11);
	levelUpToMaxEffect = new LevelUpEffect("res/effect/level_up_max.bmp", 100, 9);

	skillEffect = new Crash("res/skill/c1_skill", 512, 256, 4, actorPos);

	playerWidth = 29;
	playerHeight = 47;

	setCollider(4, 12);
}


Character::~Character()
{
	delete player_m;
	delete player_l;

}

void Character::setBuff(PlayerBuffType type)
{
	switch (type)
	{
	case ADD_DAMAGE:
		if (damage >= 10)
			break;
		damage++;
		normalBullet->setDamage(damage);
		angleBullet->setDamage(damage / 2);
		break;
	case ADD_HEATH:
		hp++;
		break;
	case ADD_SKILL:
		skill++;
		break;
	case ADD_EXP:
		if (level >= 4)
			break;
		exp++;
		if(exp > level * 2)
		{
			level++;
			switch (level)
			{
			case 1:
				addLevelEffect(levelUpTo2Effect);
				break;
			case 2:
				addLevelEffect(levelUpTo3Effect);
				break;
			case 3:
				addLevelEffect(levelUpToMaxEffect);
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

void Character::onStart()
{
	normalBullet->setDamage(damage);	

	actorPos.x = 160;
	actorPos.y = 500;
}

void Character::update(CDC * dc, CDC * canvasDC)
{
	shooter->tick();
	move();

	if(invincible)
	{
		invincibleStage(dc, canvasDC);
		return;
	}

	if (Input::getInstance().keyZDown)
		shoot();

	if (Input::getInstance().keyXDown)
		useSkill();

	skillTimer += Time.detlaTime;
	drawHero(dc, canvasDC);
}

void Character::move()
{
	left = false;
	right = false;

	if (Input::getInstance().keyLeftDown)
	{
		left = true;
	}
		

	if (Input::getInstance().keyRightDown)
	{
		right = true;
	}

	const Point perPoint = actorPos;

	actorPos.x += InputSignal::getInstance().getXSignal() * speed;
	actorPos.y += InputSignal::getInstance().getYSignal() * speed;

	if (actorPos.x < 0 || actorPos.x > 370)
		actorPos.x = perPoint.x;

	if (actorPos.y < 0 || actorPos.y > 520)
		actorPos.y = perPoint.y;
}

int Character::getHp() const
{
	return hp;
}

int Character::getSkillCount() const
{
	return skill;
}

int Character::getAtk() const
{
	return damage;
}

int Character::getLevel() const
{
	return level;
}

void Character::shoot()
{
	Bullet * newBullet = shooter->fire();
	if (!newBullet)
		return;

	shootNormalBullet();
	shootAngleBullet(level * 2 == 2 ? 2 : 4);
}

void Character::reset()
{
	Actor::setAttributes(6, 5, 5, 1);


	damage = 1;
	right = false;
	left = false;
	skill = 3;
	exp = 0;
	skillTimer = 1000;
	skillCD = 1500;
	invincible = false;
	die = false;
	invincibleTimer = 0;
	invincibleFrame = 0;

	normalBullet->setDamage(damage);
	angleBullet->setDamage(damage);

	actorPos.x = 160;
	actorPos.y = 500;


}


Rect Character::getCollider()
{
	const Rect c(actorPos.x + static_cast<int>((playerWidth - width) / 2),
		   actorPos.y + static_cast<int>((playerHeight - height) / 2),
		   width,
		   height);
	return c;
}

#pragma once
#include "Actor.h"
#include "Animation.h"
#include "NormalBullet.h"
#include "PlayerAngleBullet.h"
#include "LevelUpEffect.h"
#include "Crash.h"


class Character :
	public Actor
{
	Animation * player_m;

	Sprite * player_l;
	Sprite * player_r;

	bool right, left;
	int playerWidth, playerHeight,exp;

	NormalBullet * normalBullet;
	PlayerAngleBullet * angleBullet;

	LevelUpEffect * levelUpTo2Effect;
	LevelUpEffect * levelUpTo3Effect;
	LevelUpEffect * levelUpToMaxEffect;

	Crash * skillEffect;


	int skill,skillCD;
	float skillTimer,invincibleTimer;

	int invincibleFrame;

	void shootAngleBullet(int num) const;
	void shootNormalBullet() const;

	void useSkill();
	void addLevelEffect(LevelUpEffect * effect);

	void drawHero(CDC * dc, CDC * canvasDC) const;
	void invincibleStage(CDC *dc, CDC *canvasDC);

public:
	Character();
	~Character();

	void setBuff(PlayerBuffType type);

	void onStart() override;
	void update(CDC* dc, CDC* canvasDC) override;
	void move() override;

	int getHp() const;
	int getSkillCount() const;
	int getAtk() const;
	int getLevel() const;

	void getHurt();

	void shoot() override;
	Rect getCollider() override;


	void reset();
	bool invincible;
	bool die;
};

